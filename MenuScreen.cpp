#include "MenuScreen.h"
#include "GameScreen.h"
#include "Game.h"
#include "Windows.h"
#include "MainMenu.h"
#include <iostream>
using namespace sf;

MenuScreen::MenuScreen(Game* game) {
    setGame(game);
    state = new MainMenu(this);
}

MenuScreen::~MenuScreen() {
    delete state;
}

void MenuScreen::handleEvent(Event &event, RenderWindow* window) {
    state->handleEvent(event, window);
}

void MenuScreen::processLogic(float delta_time, RenderWindow* window) {
}

void MenuScreen::render(RenderWindow* window) {
    state->render(window);
}