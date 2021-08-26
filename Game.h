#ifndef _GAME_H_
#define _GAME_H_
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "MenuScreen.h"
#include "Screen.h"
using namespace sf;
class Game {
public:
	Game(bool vsAI);

	void run();

	void setMode(bool vsAI);

	void stopGame();

	Player* getPlayer();

	Screen* screen;
	friend class MenuScreen;
	friend class GameScreen;
private:
	bool turn; // ���������� ������������ ��� ��� (false - ������ �����, true - ������ �����)
	bool vsAI; // ������ �� ������ ���� ��� ���

	Player* player;
	
	bool is_running = true;
	
	RenderWindow* gameWindow;
	Clock clock;
};
#endif