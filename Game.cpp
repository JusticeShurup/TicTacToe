#include "Game.h"
#include "MenuScreen.h"
#include <iostream>



Game::Game(bool vsAI) : vsAI(vsAI) {
    ContextSettings settings;
    settings.antialiasingLevel = 10;
    gameWindow = new RenderWindow(VideoMode(550, 450), "TicTacToe", Style::Default, settings);
    player = new Player(1);
    is_running = true;
    turn = true;
    screen = new MenuScreen(this);
}

void Game::setMode(bool vsAI) {
    this->vsAI = vsAI;
}

void Game::stopGame() {
    is_running = false;
}

Player* Game::getPlayer() {
    return player;
}


void Game::run() {
    while (is_running) {
        Event event;
        while (gameWindow->pollEvent(event)) {
            if (event.type == Event::Closed) {
                is_running = false;
                gameWindow->close();
                break;
            }
            screen->handleEvent(event, gameWindow);
            screen->render(gameWindow);
        }
    }
}


