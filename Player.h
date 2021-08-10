#ifndef _PLAYER_H_
#define _PLAYER_H
#include <SFML/Graphics.hpp>

using namespace sf;


class Player
{
public:
	Player(int number);
	int getNumber();
private:
	int number;
};

struct GameShape {
	GameShape(float sX, float eX, float sY, float eY);
	void setPlayerShape(Player* player);
	void drawPlayerShape(RenderWindow* window);

	float startX;
	float endX;
	float startY;
	float endY;
	bool enabled = false;
	int player_number;
	RectangleShape* rectangle1; 
	RectangleShape* rectangle2;
	CircleShape* circle;
};
#endif