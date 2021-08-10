#ifndef _GAME_H_
#define _GAME_H_
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

class Game {
public:
	Game(Vector2f shapeSize, bool vsAI);

	bool checkWin(int number);
	void setClick(float X, float Y, Player* player);
	
	void run();
	void update(Player* player);
	void render();

	void simulateAI(int AI_number);

private:
	bool turn; // ѕеременна€ обозначающа€ чей ход (false - первый игрок, true - второй игрок)
	bool vsAI; // »граем ли против бота или нет

	Player* player1;
	Player* player2;

	std::vector<RectangleShape> shapes; // ѕросто квадратики дл€ отрисовки
	std::vector<GameShape> gameShapes; // »гровые квадратики-структуры - пол€
	bool is_running = true;
	RenderWindow* gameWindow;
	Clock clock;
};
#endif