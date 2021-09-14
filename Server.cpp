#include "Server.h"
#include <functional>
#include <thread>
#include <string>
#include <iostream>
#include <stdint.h>
#include <stdexcept>

Server::Server(Poco::Net::StreamSocket& client) :
	client(client),
	size(0),
	flag(false),
	adapter(*this, &Server::NetEvent)
{}

void Server::NetEvent() {
	uint8_t message = 1; 
	client.sendBytes(&message, sizeof(uint8_t));
	client.receiveBytes(&message, sizeof(uint8_t));
	client.receiveBytes(&size, sizeof(uint8_t));
	player_name = std::string(size, ' ');
	client.receiveBytes(&(player_name[0]), size);
	if (player_name.size() > 0) flag = true;
}

std::string Server::getSecondPlayerNickname() const{
	if (!flag) throw std::logic_error("nickname is not ready");
	return player_name;
}

bool Server::isNicknameRecieved() {
	if (flag) return true;
	else return false;
}

void Server::run() {
	thread.start(adapter);
}

void Server::close() {
	thread.join();
}