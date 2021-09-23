#include "SettingsMenu.h"
#include "MenuScreen.h"
#include "MainMenu.h"

using namespace sf;
SettingsMenu::SettingsMenu(MenuScreen* menuScreen) {
	this->menuScreen = menuScreen;
	textField = new TextField(40);
	okButton = new Button(100, 100, 300, 300, "Ok");
	backButton = new Button(100, 100, 0, 300, "Back");
}

SettingsMenu::~SettingsMenu() {
	delete textField;
	delete okButton;
	delete backButton;
}

void SettingsMenu::handleEvent(Event& event, RenderWindow* window) {
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

		}
		else if (backButton->isClicked()) {
			menuScreen->state = new MainMenu(menuScreen);
		}
	}
}

void SettingsMenu::render(RenderWindow* window) {
	window->clear();
	textField->draw(*window, RenderStates::Default);
	okButton->render(window);
	backButton->render(window);
	window->display();
}