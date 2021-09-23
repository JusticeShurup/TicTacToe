#include "Screen.h"
#include "Player.h"
#include "Game.h"

void Screen::setScreen(Screen* screen) {
	game->screen = screen;
	delete this;
}

void Screen::sendNameBytes(char(&buffer)[18]) {
	Poco::Net::StreamSocket socket = game->getPlayer()->getSock();
	int total_sent = 0;
	int buffer_length = 18;
	while (total_sent < buffer_length) {
		int actually_sent = socket.sendBytes(

			buffer + total_sent,
			buffer_length - total_sent
		);
		total_sent += actually_sent;
	}
}

void Screen::receiveNameBytes(char(&buffer)[18]) {
	Poco::Net::StreamSocket socket = game->getPlayer()->getSock();
	int total_received = 0;
	while (total_received < 18) {
		int actually_received = socket.receiveBytes(
			buffer + total_received,
			18 - total_received
		);
		total_received += actually_received;
	}
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