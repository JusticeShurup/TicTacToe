#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(MenuScreen* menuScreen) {
	this->menuScreen = menuScreen;
	buttonOk = new Button(100, 50, 300, 300, "Ok");
}

void SettingsMenu::handleEvent(sf::Event& event, sf::RenderWindow* window) {

}

void SettingsMenu::render(sf::RenderWindow* window) {

}