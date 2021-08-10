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
	bool turn; // ���������� ������������ ��� ��� (false - ������ �����, true - ������ �����)
	bool vsAI; // ������ �� ������ ���� ��� ���

	Player* player1;
	Player* player2;

	std::vector<RectangleShape> shapes; // ������ ���������� ��� ���������
	std::vector<GameShape> gameShapes; // ������� ����������-��������� - ����
	bool is_running = true;
	RenderWindow* gameWindow;
	Clock clock;
};
#endif