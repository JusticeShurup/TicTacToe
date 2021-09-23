#include "LobbyMenu.h"
#include "PlayMenu.h"
#include "MenuScreen.h"
#include "MainMenu.h"
#include "PlayVSPlayerMenu.h"
#include "Game.h"
#include "GameScreen.h"
#include <iostream>

using namespace sf;

LobbyMenu::LobbyMenu(MenuScreen* menuScreen) :
	buffer{0}
{
	setMenuScreen(menuScreen);
	menuScreen->setServer(new Server(menuScreen->getPlayer()->getSock()));
	font.loadFromFile("Inconsolata_Condensed-Bold.ttf");
	readyButton = new Button(150, 100, 395, 345, "Ready");
	exitButton = new Button(150, 100, 5, 345, "Exit");

	game_name = new Text();
	game_name->setString(receiveGameName());
	game_name->setFont(font);
	game_name->setFillColor(Color::Red);
	game_name->setStyle(Text::Bold);
	game_name->setCharacterSize(50);
	game_name->setPosition((550 / 2) - game_name->getGlobalBounds().width / 2, 0);

	player1_nickname = new Text();
	player1_nickname->setFont(font);
	player1_nickname->setString(menuScreen->getGame()->getPlayer()->getNickame());
	player1_nickname->setFillColor(Color::White);
	player1_nickname->setStyle(Text::Bold);
	player1_nickname->setCharacterSize(30);
	player1_nickname->setPosition(5, 100);


	player2_nickname = nullptr;
	menuScreen->getServer()->run();

}

LobbyMenu::~LobbyMenu() {
	delete readyButton;
	delete exitButton;
	delete game_name;
	delete player1_nickname;
	delete player2_nickname;
}

std::string LobbyMenu::receiveGameName() {
	Poco::Net::StreamSocket sock = menuScreen->getGame()->getPlayer()->getSock();
	menuScreen->receiveNameBytes(buffer);

	std::string game_name(buffer + 1);
	uint8_t result = 1;
	sock.sendBytes(&result, sizeof(uint8_t));
	return game_name;
}

void LobbyMenu::initPlayer2(std::string name) {
	menuScreen->getServer()->close();
	player2_nickname = new Text();
	player2_nickname->setFont(font);
	player2_nickname->setString(name);
	player2_nickname->setFillColor(Color::White);
	player2_nickname->setStyle(Text::Bold);
	player2_nickname->setCharacterSize(30);
	player2_nickname->setPosition(545 - player2_nickname->getGlobalBounds().width, 100);
}

void LobbyMenu::handleEvent(Event& event, RenderWindow* window) {
	readyButton->update(Vector2f(Mouse::getPosition(*window)), event);
	exitButton->update(Vector2f(Mouse::getPosition(*window)), event);
	try {
		initPlayer2(menuScreen->getServer()->getSecondPlayerNickname());
	}
	catch(std::logic_error &e){
	}
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		uint8_t ready;
		if (readyButton->isClicked()) {
			ready = 1;
			menuScreen->getPlayer()->getSock().sendBytes(&ready, sizeof(uint8_t));
			ready = 0;
			menuScreen->getPlayer()->getSock().receiveBytes(&ready, sizeof(uint8_t));
			uint8_t game_number;
			if (ready == 1) {
				menuScreen->getPlayer()->getSock().receiveBytes(&game_number, sizeof(uint8_t));
				menuScreen->getGame()->getPlayer()->setNumber(game_number);
				std::cout << menuScreen->getGame()->getPlayer()->getNumber();
				menuScreen->setScreen(new GameScreen(menuScreen->getGame()));
			}
		}
		else if (exitButton->isClicked()) {
			ready = 2;
			menuScreen->getPlayer()->getSock().sendBytes(&ready, sizeof(ready));
			menuScreen->state->setNewState(new PlayVSPlayerMenu(menuScreen));
		}
	}
}

void LobbyMenu::render(RenderWindow* window) {
	window->clear();
	readyButton->render(window);
	exitButton->render(window);
	window->draw(*game_name);
	if (player1_nickname) window->draw(*player1_nickname);
	if (player2_nickname) window->draw(*player2_nickname);
	window->display();
}

