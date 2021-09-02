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
	std::string nickname = "";
	client.sendBytes(&message, sizeof(uint8_t));
	client.receiveBytes(&message, sizeof(uint8_t));
	while (nickname.size() <= 0) {
		client.receiveBytes(&size, sizeof(uint8_t));
		nickname = std::string(size, ' ');
		client.receiveBytes(&(nickname[0]), size);
		player_name = nickname;
	}
	if (nickname.size() > 0) flag = true;
}

std::string Server::getSecondPlayerNickname() const{
	if (flag) return player_name;
	else throw std::logic_error("nickname is not ready");
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