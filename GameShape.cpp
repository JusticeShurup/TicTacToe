#include "GameShape.h"

using namespace sf;

GameShape::GameShape(float sX, float eX, float sY, float eY)
	: startX(sX),
	endX(eX),
	startY(sY),
	endY(eY) {
	rectangle1 = nullptr;
	rectangle2 = nullptr;
	circle = nullptr;
	player_number = 0;
}

void GameShape::setPlayerShape(int player_number) {
	this->player_number = player_number;
	if (player_number == 1) {

		rectangle1 = new RectangleShape(Vector2f(180, 10));
		rectangle1->setFillColor(Color::Black);
		rectangle1->setOrigin(180 / 2, 10 / 2);
		rectangle1->setPosition((startX + endX) / 2, (startY + endY) / 2);
		rectangle1->setRotation(45);
		rectangle1->move(-3, 0);

		rectangle2 = new RectangleShape(Vector2f(180, 10));
		rectangle2->setFillColor(Color::Black);
		rectangle2->setOrigin(180 / 2, 10 / 2);
		rectangle2->setPosition((startX + endX) / 2, (startY + endY) / 2);
		rectangle2->setRotation(135);
		rectangle2->move(-3, 0);
	}
	else if (player_number == 2) {

		circle = new CircleShape(50);
		circle->setOutlineColor(Color::Black);
		circle->setOutlineThickness(10);
		circle->setPointCount(50);
		circle->setPosition((startX + endX) / 2 - circle->getRadius(), (startY + endY) / 2 - circle->getRadius());

	}
}

void GameShape::clearShape() {
	delete rectangle1;
	delete rectangle2;
	delete circle;
	rectangle1 = nullptr;
	rectangle2 = nullptr;
	circle = nullptr;
}

void GameShape::drawPlayerShape(RenderWindow* window) {
	if (rectangle1 && rectangle2) {
		window->draw(*rectangle1);
		window->draw(*rectangle2);
	}
	else if (circle) {
		window->draw(*circle);
	}
}