#include "GameScreen.h"
#include "Game.h"
#include "ResultScreen.h"
#include "GameShape.h"
#include <iostream>
using namespace sf;

GameScreen::GameScreen(Game* game) :
    buffer{ 0 },
    claimed_shapes{ 10 }
{
    setGame(game);
    claimTurnImage = new Image;
    claimTurnImage->loadFromFile("images/claimButton.png");
    claimTurnTexture = new Texture;
    claimTurnTexture->loadFromImage(*claimTurnImage);
    claimTurnButton = new RectangleShape(Vector2f(105, 150));
    claimTurnButton->setTexture(claimTurnTexture);
    claimTurnButton->setPosition(455, 300);
    claimTurnButton->setFillColor(Color::White);
    Vector2f shapeSize(150, 150);
    claimTurn = false;
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
    gameShape_number = 15;
    turn = true;
    vsAI = game->vsAI;
}


void GameScreen::update(int player_number, Event& event) {
    setClick(event.mouseButton.x, event.mouseButton.y, player_number);
}

bool GameScreen::checkWin(int number) {
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
    game->is_running = false;
    std::cout << "Nobody win" << std::endl;
    return false;
}

void GameScreen::setClick(float X, float Y, int player_number) {
    for (int i = 0; i < 9; i++) {
        if (!gameShapes[i].enabled) {
            if (shapes[i].getGlobalBounds().contains(X, Y)) {
                gameShapes[i].enabled = true;
                gameShapes[i].setPlayerShape(player_number);
                if (vsAI) {
                    if (turn) turn = false;
                    else turn = true;
                }
                gameShape_number = i;
                break;
            }
        }
    }
}

void GameScreen::undoClick() {
    if (gameShape_number == 15) gameShape_number = 0;
    for (auto i : claimed_shapes) {
        if (gameShape_number == i) {
            return;
        }
    }
    gameShapes[gameShape_number].enabled = false;
    gameShapes[gameShape_number].clearShape();
    if (vsAI) turn = true;
}

void GameScreen::simulateAI(int AI_number) {
    srand(time(NULL));
    while (true)
    {
        Sleep(100);
        int choice = rand() % 9;
        if (!gameShapes[choice].enabled) {
            gameShapes[choice].enabled = true;
            if (AI_number == 1) {
                gameShapes[choice].setPlayerShape(AI_number);
            }
            else {
                gameShapes[choice].setPlayerShape(AI_number);
            }
            if (turn) turn = false;
            else turn = true;
            break;
        }
    }
}

void GameScreen::handleEvent(Event &event, RenderWindow* window) {
    int AI_number;
    srand(time(NULL));
    bool is_running = true;
    turn = 0;
    if (!vsAI) {
        game->player->getSock().receiveBytes(&turn, sizeof(uint8_t));
        while (is_running) {
            if (turn == 0) {
                std::cout << "Works" << std::endl;
                game->getPlayer()->getSock().receiveBytes(&buffer, 9);
                std::cout << "get it" << std::endl;
                for (int i = 0; i < 9; i++) {
                    gameShapes[i].setPlayerShape(buffer[i]);
                    gameShapes[i].enabled = (buffer[i] == 1 || buffer[i] == 2);
                    claimed_shapes[i] = (gameShapes[i].enabled ? i : 15);
                }
                game->player->getSock().receiveBytes(&turn, sizeof(uint8_t));
            }
            while (window->pollEvent(event)) {
                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                    if (claimTurnButton->getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window)))) {
                        claimTurn = true;
                        uint8_t shape_number = gameShape_number;
                        game->player->getSock().sendBytes(&shape_number, sizeof(uint8_t));
                        std::cout << "sent" << std::endl;
                        game->player->getSock().receiveBytes(buffer, 9);
                        for (int i = 0; i < 9; i++) {
                            gameShapes[i].setPlayerShape(buffer[i]);
                            gameShapes[i].enabled = (buffer[i] == 1 || buffer[i] == 2);
                            claimed_shapes[i] = (gameShapes[i].enabled ? i : 15);
                        }
                        turn = 0;
                    }
                    else {
                        undoClick();
                        update(game->player->getNumber(), event);
                    }
                    if (checkWin(game->getPlayer()->getNumber())) {
                        std::cout << "Win player 1" << std::endl;
                        is_running = false;
                    }
                }
                render(window);
            }
        }
        game->screen = new ResultScreen(game);
    }
    else {
        int player_number = game->player->getNumber();
        if (player_number == 1) {
            AI_number = 2;
        }
        else {
            AI_number = 1;
        }
        turn = 1;
        while (is_running) {
            game->clock.restart();
            while (turn) {
                while (!claimTurn) {
                    while (window->pollEvent(event)) {
                        if (player_number == 1 && event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                            if (claimTurnButton->getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window)))) {
                                claimTurn = true;
                                claimed_shapes[gameShape_number] = gameShape_number;
                            }
                            else {
                                undoClick();
                                std::cout << "fuck" << std::endl;
                                update(game->player->getNumber(), event);
                            }
                        }
                        else if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                            if (claimTurnButton->getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window)))) {
                                claimTurn = true;
                                claimed_shapes[gameShape_number] = gameShape_number;
                            }
                            else {
                                undoClick();
                                update(game->player->getNumber(), event);
                            }
                        }

                        render(window);
                    }
                }
                if (checkWin(game->player->getNumber())) {
                    std::cout << "You win" << std::endl;
                    is_running = false;
                    render(window);
                    break;
                }
            }
            while (!turn) {
                simulateAI(AI_number);
                if (checkWin(AI_number)) {
                    std::cout << "You lost" << std::endl;
                    render(window);
                    is_running = false;
                }
                claimTurn = false;
            }
            render(window);
        }

    }
    render(window);
    game->screen = new ResultScreen(game);
}

void GameScreen::processLogic(float delta_time, RenderWindow* window) {
    
}

void GameScreen::render(RenderWindow* window) {
    Event event;

    while (window->pollEvent(event)) {
        if (event.type == Event::Closed()) {
            window->close();
        }
    }

    window->clear();
    for (int i = 0; i < shapes.size(); i++) {
        window->draw(shapes[i]);
        if (gameShapes[i].enabled) {
            gameShapes[i].drawPlayerShape(window);
        }
        window->draw(*claimTurnButton);
    }
    window->display();
}
