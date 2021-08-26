#include "FindRoomMenu.h"
#include "MenuScreen.h"
#include "Game.h"
#include "PlayVSPlayerMenu.h"
#include "Poco/Net/StreamSocket.h"
#include <iostream>
using namespace sf;

FindRoomMenu::FindRoomMenu(MenuScreen* menuScreen) {
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
			menuScreen->getGame()->getPlayer2()->setConnection("127.0.0.1:1337");

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