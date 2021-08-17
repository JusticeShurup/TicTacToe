#include "PlayMenu.h"
#include "MenuScreen.h"
#include "MainMenu.h"
#include "PlayVSPlayerMenu.h"
#include "Game.h"
#include "GameScreen.h"

using namespace sf;

PlayMenu::PlayMenu(MenuScreen* menuScreen) {
	setMenuScreen(menuScreen);
    playVSAIButton = new Button(540, 100 , 5, 5, "Play vs Bot");
    playVSPlayerButton = new Button(540, 100, 5, 115, "Play vs Player");
    backButton = new Button(550, 100, 0, 350, "Back");
}

PlayMenu::~PlayMenu() {
	delete playVSAIButton;
	delete playVSPlayerButton;
	delete backButton;
}

void PlayMenu::handleEvent(Event& event, RenderWindow* window) {
    playVSAIButton->update(Vector2f(Mouse::getPosition(*window)), event);
    playVSPlayerButton->update(Vector2f(Mouse::getPosition(*window)), event);
    backButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
        if (playVSAIButton->isClicked()) {
            menuScreen->getGame()->setMode(1);
            menuScreen->getGame()->screen = new GameScreen(menuScreen->getGame());
        }
        else if (playVSPlayerButton->isClicked()) {
            menuScreen->getGame()->setMode(0);
            menuScreen->state = new PlayVSPlayerMenu(menuScreen);
        }
        else if (backButton->isClicked()) {
            menuScreen->state = new MainMenu(menuScreen);
        }
    }
}

void PlayMenu::render(RenderWindow* window) {
    window->clear();
    playVSAIButton->render(window);
    playVSPlayerButton->render(window);
    backButton->render(window);
    window->display();
}