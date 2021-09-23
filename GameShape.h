#ifndef _GAME_SHAPE_H_
#define _GAME_SHAPE_H_
#include <SFML/Graphics.hpp>
#include "Player.h"

class GameShape
{
public:
	GameShape(float sX, float eX, float sY, float eY);
	void setPlayerShape(int player_number);
	void drawPlayerShape(sf::RenderWindow* window);
	void clearShape();


	float startX;
	float endX;
	float startY;
	float endY;
	bool enabled = false;
	int player_number;
	sf::RectangleShape* rectangle1;
	sf::RectangleShape* rectangle2;
	sf::CircleShape* circle;
};
#endif

