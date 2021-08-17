#include "ResultScreen.h"
#include "Game.h"
#include "MenuScreen.h"

using namespace sf;

ResultScreen::ResultScreen(Game* game) {
	set_game(game);
	okButton = new Button(50, 50, 250, 250, "Ok");
}

ResultScreen::~ResultScreen() {
	delete okButton;
}

void ResultScreen::handleEvent(Event& event, RenderWindow* window) {
	okButton->update(Vector2f(Mouse::getPosition(*window)), event);
	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
		if (okButton->isClicked()) {
			game->screen = new MenuScreen(game);
		}
	}
}

void ResultScreen::processLogic(float delta_time, RenderWindow* window) {

}

void ResultScreen::render(RenderWindow* window) {
	window->clear();
	okButton->render(window);
	window->display();
}