#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <SFML/Graphics.hpp>
#include "Button.h"

class Game;

class Screen
{
protected:
	
	Game* game;

public:
	
	void set_game(Game* game);
	Game* getGame();
	
	virtual ~Screen() {};

	virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) = 0;
	virtual void processLogic(float delta_time, sf::RenderWindow* window) = 0;
	virtual void render(sf::RenderWindow* window) = 0;


};
#endif

