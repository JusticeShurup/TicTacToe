#include "FindRoomMenu.h"
#include "MenuScreen.h"
#include "Game.h"
#include "LobbyMenu.h"
#include "PlayVSPlayerMenu.h"
#include "Poco/Net/StreamSocket.h"
#include <iostream>
using namespace sf;

FindRoomMenu::FindRoomMenu(MenuScreen* menuScreen) : name_buffer{0} {
	setMenuScreen(menuScreen);
	textField = new TextField(40);
	textField->setPosition(0, 20);
	okButton = new Button(200, 100, 300, 200, "Ok");
	backButton = new Button(550, 100, 0, 350, "Back");

}

FindRoomMenu::~FindRoomMenu() {
	delete textField;
	delete okButton;
	delete backButton;
}

void FindRoomMenu::handleEvent(Event& event, RenderWindow* window) {
	uint8_t result;
	okButton->update(Vector2f(Mouse::getPosition(*window)), event);
	backButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (textField->contains(sf::Vector2f(Mouse::getPosition(*window)))) {
		textField->setActive(true);
	}
	else {
		textField->setActive(false);
	}
	textField->handleInput(event);
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		if (okButton->isClicked()) {
			std::string game_name;
			game_name = textField->getText();
			uint8_t size = game_name.size();
			name_buffer[0] = size;
			strncpy(name_buffer + 1, game_name.c_str(), size+1);
			menuScreen->getGame()->getPlayer()->getSock().sendBytes(name_buffer, MAX_NAME_LENGHT);
			menuScreen->getGame()->getPlayer()->getSock().receiveBytes(&result, sizeof(uint8_t));
			if (result == 1) {
				uint8_t message = 1;
				menuScreen->getGame()->getPlayer()->getSock().sendBytes(&message, sizeof(uint8_t));
				setNewState(new LobbyMenu(menuScreen));
			}
			else {
				menuScreen->getGame()->getPlayer()->getSock().close();
				setNewState(new PlayVSPlayerMenu(menuScreen));
			}
		}
		else if (backButton->isClicked()) {
			menuScreen->state = new PlayVSPlayerMenu(menuScreen);
		}
	}
}

void FindRoomMenu::render(RenderWindow* window) {
	window->clear();
	textField->draw(*window, RenderStates::Default);
	okButton->render(window);
	backButton->render(window);
	window->display();
}