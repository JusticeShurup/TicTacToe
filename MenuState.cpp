#include "MenuState.h"
#include "MenuScreen.h"

void MenuState::setMenuScreen(MenuScreen* menuScreen) {
	this->menuScreen = menuScreen;
}

void MenuState::setNewState(MenuState* menuState) {
	menuScreen->state = menuState;
	delete this;
}