#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>

enum button_states{ BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
public:

	Button(float widht, float height, float posX, float posY, std::string buttonText);
	
	bool isClicked();
	void update(sf::Vector2f pos, sf::Event& event);
	void render(sf::RenderWindow* window);

private: 
	
	short unsigned state;

	float widht;
	float height;

	float posX;
	float posY;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	std::string buttonText;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
};
#endif