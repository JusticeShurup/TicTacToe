#ifndef _TEXT_FIELD_H_
#define _TEXT_FIELD_H_
#include <SFML/Graphics.hpp>
class TextField : public sf::Transformable, public sf::Drawable
{
public:
	TextField(int size);
	std::string getText();
	void setPosition(float x, float y);
	bool contains(sf::Vector2f point);
	void setActive(bool active);
	void handleInput(sf::Event& event);
	virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

private:
	int size;
	sf::Font font;
	std::string text;
	sf::Text textSF;
	sf::RectangleShape rect;
	bool active;
};
#endif

