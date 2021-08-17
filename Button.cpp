#include "Button.h"
#include <iostream>

using namespace sf;

Button::Button(float widht, float height, float posX, float posY, std::string name) 
	: widht(widht), height(height), posX(posX), posY(posY), buttonText(name) 
{
	state = BTN_IDLE;
	shape = RectangleShape(Vector2f(widht, height));
	shape.setPosition(Vector2f(posX, posY));
	shape.setOutlineThickness(5);

	font.loadFromFile("Inconsolata_Condensed-Bold.ttf");

	text.setFont(font);
	text.setCharacterSize(75);
	text.setFillColor(Color::Black);
	text.setString(name);
	text.setPosition(shape.getPosition().x + ((shape.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2)),
					 shape.getPosition().y);
}

bool Button::isClicked() {
	if (state == BTN_ACTIVE) {
		return true; 
	}
	else return false;
}

void Button::update(Vector2f pos, Event& event) {
	state = BTN_IDLE;
	//Hover
	if (shape.getGlobalBounds().contains(pos))
	{
		state = BTN_HOVER;
		//Pressed
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			state = BTN_ACTIVE;
		}
	}

	switch (state)
	{
	case BTN_IDLE:
		this->shape.setFillColor(Color::White);
		this->text.setFillColor(Color::Black);
		this->shape.setOutlineColor(Color::White);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(Color::White);
		this->text.setFillColor(Color::Red);
		this->shape.setOutlineColor(Color(127, 127, 127));
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(Color::White);
		this->text.setFillColor(Color::Red);
		this->shape.setOutlineColor(Color(127, 127, 127));
		break;

	default:
		this->shape.setFillColor(Color::White);
		this->text.setFillColor(Color::Black);
		this->shape.setOutlineColor(Color::White);
		break;
	}
}

void Button::render(RenderWindow* window) {
	window->draw(shape);
	window->draw(text);
}

