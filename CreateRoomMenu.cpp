#include "CreateRoomMenu.h"
#include "PlayVSPlayerMenu.h"
#include "MenuScreen.h"
#include "Game.h"
#include <Poco/Net/StreamSocket.h>
#include "LobbyMenu.h"
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
			game_name = textField->getText();
			uint8_t size = game_name.size();
			char* buffer = new char[size+1];
			buffer[0] = size;
			strcpy(buffer + 1, game_name.c_str());
			menuScreen->getGame()->getPlayer()->getSock().sendBytes(buffer, size+1);
			menuScreen->state->setNewState(new LobbyMenu(menuScreen));
			delete[] buffer;
		}
		else if (backButton->isClicked()) {
			menuScreen->getGame()->getPlayer()->getSock().close();
			menuScreen->state->setNewState(new PlayVSPlayerMenu(menuScreen));
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