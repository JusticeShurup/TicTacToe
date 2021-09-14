#include "Screen.h"
#include "Player.h"
#include "Game.h"

void Screen::setScreen(Screen* screen) {
	game->screen = screen;
	delete this;
}

void Screen::setGame(Game *game) {
	this->game = game;
}

void Screen::setServer(Server* server) {
	this->server = server;
}

Game* Screen::getGame() {
	return game;
}

Server* Screen::getServer() {
	return server;
}


Player* Screen::getPlayer() {
	return game->getPlayer();
}