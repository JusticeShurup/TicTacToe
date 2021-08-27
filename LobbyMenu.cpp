#include "LobbyMenu.h"
#include "PlayMenu.h"
#include "MenuScreen.h"
#include "MainMenu.h"
#include "PlayVSPlayerMenu.h"
#include "Game.h"
#include "GameScreen.h"
#include <iostream>

using namespace sf;

LobbyMenu::LobbyMenu(MenuScreen* menuScreen) {
	setMenuScreen(menuScreen);

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
	player1_nickname->setString("Player");
	player1_nickname->setFillColor(Color::White);
	player1_nickname->setStyle(Text::Bold);
	player1_nickname->setCharacterSize(30);
	player1_nickname->setPosition(5, 100);

	menuScreen->getServer()->run();

	player2_nickname = nullptr;
}

LobbyMenu::~LobbyMenu() {
	delete readyButton;
	delete exitButton;
	delete game_name;
	delete player1_nickname;
	delete player2_nickname;
	menuScreen->getServer()->close();
}

std::string LobbyMenu::receiveGameName() {
	uint8_t size;
	menuScreen->getGame()->getPlayer()->getSock().receiveBytes(&size, sizeof(uint8_t));
	std::string game_name(size, ' ');
	menuScreen->getGame()->getPlayer()->getSock().receiveBytes(&(game_name[0]), size);
	return game_name;
}

void LobbyMenu::initPlayer2(std::string name) {
	player2_nickname = new Text();
	player2_nickname->setFont(font);
	player2_nickname->setString(name);
	player2_nickname->setFillColor(Color::White);
	player2_nickname->setStyle(Text::Bold);
	player2_nickname->setCharacterSize(30);
	player2_nickname->setPosition(5, 400 - player2_nickname->getGlobalBounds().width / 2);
}

void LobbyMenu::handleEvent(Event& event, RenderWindow* window) {
	readyButton->update(Vector2f(Mouse::getPosition(*window)), event);
	exitButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (!player2_nickname) {
		std::cout << "nig" << std::endl;
		std::string name(buffer, buffer[0]);
		initPlayer2(name);
	}
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		if (readyButton->isClicked()) {

		}
		else if (exitButton->isClicked()) {
			menuScreen->getGame()->getPlayer()->getSock().close();
			menuScreen->state = new PlayVSPlayerMenu(menuScreen);
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

