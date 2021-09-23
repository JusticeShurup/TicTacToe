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
	textField->handleInput(event);
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		if (textField->contains(Vector2f(Mouse::getPosition(*window)))) {
			textField->setActive(true);
		}
		else {
			textField->setActive(false);
		}
		if (okButton->isClicked()) {
			std::string game_name;
			game_name = textField->getText();
			uint8_t size = game_name.size();
			*((uint8_t*)name_buffer) = size;
			strcpy(name_buffer + sizeof(uint8_t), game_name.c_str());
			
			menuScreen->sendNameBytes(name_buffer);

			menuScreen->getGame()->getPlayer()->getSock().receiveBytes(&result, sizeof(uint8_t));
			if (result == 1) {
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