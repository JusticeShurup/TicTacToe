#include "Game.h"
#include "MenuScreen.h"
#include <iostream>



Game::Game(bool vsAI) : vsAI(vsAI) {
    ContextSettings settings;
    settings.antialiasingLevel = 10;
    gameWindow = new RenderWindow(VideoMode(550, 450), "TicTacToe", Style::Default, settings);
    player1 = new Player(1);
    player2 = new Player(2);
    is_running = true;
    turn = true;
}

void Game::setMode(bool vsAI) {
    this->vsAI = vsAI;
}

void Game::stopGame() {
    is_running = false;
}

Player* Game::getPlayer1() {
    return player1;
}

Player* Game::getPlayer2() {
    return player2;
}

void Game::run() {
    screen = new MenuScreen(this);
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


