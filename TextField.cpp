#include "TextField.h"
#include <SFML/System.hpp>

using namespace sf;
TextField::TextField(int size) : 
	size(size),
	rect(sf::Vector2f(15 * size, 50)), 
	active(false)
{
	font.loadFromFile("Inconsolata_Condensed-Bold.ttf");
	textSF.setFont(font);
	textSF.setCharacterSize(30);
	textSF.setFillColor(Color::Black);
	rect.setOutlineThickness(2);
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color(127, 127, 127));
	rect.setPosition(this->getPosition());

	textSF.setString("|");
}

std::string TextField::getText() {
	return text;
}

void TextField::setPosition(float x, float y) {
	Transformable::setPosition(x, y);
	rect.setPosition(x, y);
	textSF.setPosition(x, y);
}

bool TextField::contains(Vector2f point) {
	return rect.getGlobalBounds().contains(point);
}

void TextField::setActive(bool active) {
	this->active = active;
	if (active) {
		rect.setOutlineColor(Color::Blue);
	}
	else {
		rect.setOutlineColor(Color(127, 127, 127));
	}
}

void TextField::handleInput(Event& event) {
	if (!active || event.type != sf::Event::TextEntered)
		return;

	if (event.text.unicode == 8) {   // Delete key
		text = text.substr(0, text.size() - 1);
	}
	else if (text.size() < size && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		text += event.text.unicode;
	}
	textSF.setString(text + "|");
}

void TextField::draw(RenderTarget& window, RenderStates states) const {
	window.draw(rect);
	window.draw(textSF);
}
