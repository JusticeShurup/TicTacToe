#include "Screen.h"

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