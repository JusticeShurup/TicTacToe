#include "Game.h"
#include <iostream>



Game::Game(Vector2f shapeSize, bool vsAI) : vsAI(vsAI) {
    ContextSettings settings;
    settings.antialiasingLevel = 10;
    gameWindow = new RenderWindow(VideoMode(450, 450), "TicTacToe", Style::Default, settings);
    player1 = new Player(1);
    player2 = new Player(2);
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            shapes.emplace_back(RectangleShape(shapeSize));
            shapes[count].setPosition(i * 150, j * 150);
            shapes[count].setOutlineColor(Color::Black);
            shapes[count].setOutlineThickness(5);
            gameShapes.emplace_back(GameShape(i * 150, (i * 150) + 150, j * 150, (j * 150) + 150));
            count += 1;
        }
    }
    is_running = true;
    turn = true;
}

bool Game::checkWin(int number) {
    for (int i = 0; i <= 6; i += 3) {
        if (gameShapes[i].enabled && gameShapes[i + 1].enabled && gameShapes[i + 2].enabled) {
            if (gameShapes[i].player_number == number && gameShapes[i + 1].player_number == number && gameShapes[i + 2].player_number == number) {
                return true;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (gameShapes[i].enabled && gameShapes[i + 3].enabled && gameShapes[i + 6].enabled) {
            if (gameShapes[i].player_number == number && gameShapes[i + 3].player_number == number && gameShapes[i + 6].player_number == number) {
                return true;
            }
        }
    }
    bool flag = true;
    for (int i = 0; i <= 8; i += 4) {
        if (!gameShapes[i].enabled) {
            flag = false;
        }
        if (gameShapes[i].player_number != number) {
            flag = false;
        }
    }
    if (flag) return true;
    flag = true;
    for (int i = 2; i <= 6; i += 2) {
        if (!gameShapes[i].enabled) {
            flag = false;
        }
        if (gameShapes[i].player_number != number) {
            flag = false;
        }
    }
    if (flag) return true;
    for (int i = 0; i < gameShapes.size(); i++) {
        if (!gameShapes[i].enabled) {
            return false;
        }
    }
    is_running = false;
    std::cout << "Nobody win" << std::endl;
    return false;
}

void Game::setClick(float X, float Y, Player *player) {
    for (int i = 0; i < 9; i++) {
        if (!gameShapes[i].enabled) {
            if (X >= gameShapes[i].startX && X <= gameShapes[i].endX
                && Y >= gameShapes[i].startY && Y <= gameShapes[i].endY) {
                gameShapes[i].enabled = true;
                gameShapes[i].setPlayerShape(player);
                if (turn) turn = false;
                else turn = true;
                break;
            }
        }
    }
}

void Game::run() {
    int AI_number;
    if (!vsAI) {
        srand(time(NULL));
        int player_number = rand() % 2 + 1;
        turn = player_number;
        while (is_running) {
            render();
            clock.restart();
            if (player_number == 1) {
                while (!turn) {
                    update(player1);
                    if (checkWin(player_number)) {
                        std::cout << player_number << " win" << std::endl;
                        is_running = false;
                    }
                }
                player_number = 2;
            }
            else {
                while (turn) {
                    update(player2);
                    if (checkWin(player_number)) {
                        std::cout << player_number << " win" << std::endl;
                        is_running = false;
                    }
                }
                player_number = 1;
            }
        }
    }
    else {
        srand(time(NULL));
        int player_number = rand() % 2 + 1;
        if (player_number == 1) {
            AI_number = 2;
        }
        else {
            AI_number = 1;
        }
        turn = 1;
        while (is_running) {
            std::cout << player_number << " " << AI_number << std::endl;
            render();
            clock.restart();
            while (turn) {
                if (player_number == 1) {
                    update(player1);
                    if (checkWin(player_number)) {
                        std::cout << "You win" << std::endl;
                        is_running = false;
                        break;
                    }
                }
                else {
                    update(player2);
                    if (checkWin(player_number)) {
                        std::cout << "You win" << std::endl;
                        is_running = false;
                        break;
                    }
                }
                render();
            }
            while (!turn) {
                simulateAI(AI_number);
                if (checkWin(AI_number)) {
                    std::cout << "You lost" << std::endl;
                    is_running = false;
                }
            }
            render();
        }

    }
    render();
    std::cin >> AI_number;
}

void Game::update(Player* player) {
    while (true) {
        if (Mouse::isButtonPressed(Mouse::Button::Left) && clock.getElapsedTime().asSeconds() > 0.25) {
            setClick(Mouse::getPosition(*gameWindow).x, Mouse::getPosition(*gameWindow).y, player);
            break;
        }
    }
}

void Game::render() {

    Event event;

    while (gameWindow->pollEvent(event)) {
        if (event.type == Event::Closed()) {
            gameWindow->close();
        }
    }

    gameWindow->clear();
    for (int i = 0; i < shapes.size(); i++) {
        gameWindow->draw(shapes[i]);
        if (gameShapes[i].enabled) {
            gameShapes[i].drawPlayerShape(gameWindow);
        }
    }
    gameWindow->display();

}

void Game::simulateAI(int AI_number) {
    srand(time(NULL));
    while (true)
    {
        int choice = rand() % 9;
        if (!gameShapes[choice].enabled) {
            gameShapes[choice].enabled = true;
            if (AI_number == 1) {
                gameShapes[choice].setPlayerShape(player1);
            }
            else {
                gameShapes[choice].setPlayerShape(player2);
            }
            if (turn) turn = false;
            else turn = true;
            break;
        }
    }
}
