#include "CreateRoomMenu.h"
#include "PlayVSPlayerMenu.h"
#include "MenuScreen.h"
#include "Game.h"
#include <Poco/Net/StreamSocket.h>
#include <iostream>

using namespace sf;

CreateRoomMenu::CreateRoomMenu(MenuScreen* menuScreen) {
	setMenuScreen(menuScreen);
	textField = new TextField(40);
	textField->setPosition(0, 20);
	okButton = new Button(200, 100, 300, 200, "Ok");
	backButton = new Button(550, 100, 0, 350, "Back");
}

CreateRoomMenu::~CreateRoomMenu() {
	delete textField;
	delete okButton;
	delete backButton;
}

void CreateRoomMenu::handleEvent(Event& event, RenderWindow* window) {
	okButton->update(Vector2f(Mouse::getPosition(*window)), event);
	backButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (textField->contains(Vector2f(Mouse::getPosition(*window)))) {
		textField->setActive(true);
	}
	else {
		textField->setActive(false);
	}
	textField->handleInput(event);
	if (event.type == event.MouseButtonReleased || event.mouseButton.button == Mouse::Left) {
		if (okButton->isClicked()) {
			std::string game_name;
			uint32_t size;
			game_name = textField->getText();
			size = game_name.size();
			std::cout << size;
			menuScreen->getGame()->getPlayer1()->setConnection("127.0.0.1:1337");
			menuScreen->getGame()->getPlayer1()->getSock().sendBytes(&size, sizeof(uint32_t));
			menuScreen->getGame()->getPlayer1()->getSock().sendBytes(game_name.c_str(), game_name.size());
		}
		else if (backButton->isClicked()) {
			menuScreen->state = new PlayVSPlayerMenu(menuScreen);
		}
	}
}

void CreateRoomMenu::render(RenderWindow* window) {
	window->clear();
	textField->draw(*window, RenderStates::Default);
	okButton->render(window);
	backButton->render(window);
	window->display();
}