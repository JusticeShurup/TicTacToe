#include "MainMenu.h"
#include "MenuScreen.h"
#include "PlayMenu.h"
#include "Game.h"
#include "SettingsMenu.h"
using namespace sf;

MainMenu::MainMenu(MenuScreen* menuScreen) {
	setMenuScreen(menuScreen);
	playButton = new Button(550, 100, 0, 0, "Play");
	settingsButton = new Button(550, 100, 0, 100, "Settings");
	exitButton = new Button(550, 100, 0, 350, "Exit");

}

MainMenu::~MainMenu() {
	delete playButton;
	delete exitButton;
}

void MainMenu::handleEvent(Event& event, RenderWindow* window) {
	playButton->update(Vector2f(Mouse::getPosition(*window)), event);
	settingsButton->update(Vector2f(Mouse::getPosition(*window)), event);
	exitButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		if (playButton->isClicked()) {
			menuScreen->state->setNewState(new PlayMenu(menuScreen));
		}
		else if (settingsButton->isClicked()) {
			menuScreen->state->setNewState(new SettingsMenu(menuScreen));
		}
		else if (exitButton->isClicked()) {
			window->close();
			menuScreen->getGame()->stopGame();
		}
	}
}

void MainMenu::render(RenderWindow* window) {
	window->clear();
	playButton->render(window);
	settingsButton->render(window);
	exitButton->render(window);
	window->display();
}
