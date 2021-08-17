#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <SFML/Graphics.hpp>
#include "Button.h"

class MenuScreen;

class MenuState
{
protected:

	MenuScreen* menuScreen;

public: 
	virtual ~MenuState() {};
	
	void setMenuScreen(MenuScreen* menuScreen);

	virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
};
#endif

