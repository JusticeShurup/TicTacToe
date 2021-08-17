#include "Screen.h"

void Screen::set_game(Game *game) {
	this->game = game;
}

Game* Screen::getGame() {
	return game;
}