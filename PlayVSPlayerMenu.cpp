#include "PlayVSPlayerMenu.h"
#include "PlayMenu.h"
#include "MenuScreen.h"
#include "CreateRoomMenu.h"
#include "FindRoomMenu.h"

using namespace sf;


PlayVSPlayerMenu::PlayVSPlayerMenu(MenuScreen* menuScreen) {
	setMenuScreen(menuScreen);
	createRoomButton = new Button(550, 100, 0, 0, "Create room");
	findRoomButton = new Button(550, 100, 0, 100, "Find room");
	backButton = new Button(550, 100, 0, 350, "Back");
}

PlayVSPlayerMenu::~PlayVSPlayerMenu() {
	delete createRoomButton;
	delete findRoomButton;
	delete backButton;
}

void PlayVSPlayerMenu::handleEvent(Event& event, RenderWindow* window) {
	createRoomButton->update(Vector2f(Mouse::getPosition(*window)), event);
	findRoomButton->update(Vector2f(Mouse::getPosition(*window)), event);
	backButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
        if (createRoomButton->isClicked()) {
			menuScreen->state = new CreateRoomMenu(menuScreen);
        }
		else if (findRoomButton->isClicked()) {
			menuScreen->state = new FindRoomMenu(menuScreen);
		}
        else if (backButton->isClicked()) {
			menuScreen->state = new PlayMenu(menuScreen);
        }
	}
}

void PlayVSPlayerMenu::render(RenderWindow* window) {
	window->clear();
	createRoomButton->render(window);
	findRoomButton->render(window);
	backButton->render(window);
	window->display();
}