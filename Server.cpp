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
	adapter(*this, &Server::NetEvent), 
	buffer{0}
{}

void Server::NetEvent() {
	uint8_t message = 1; 
	int total_received = 0;
	while (total_received < 18) {
		int actually_received = client.receiveBytes(
			buffer + total_received,
			18 - total_received
		);

		total_received += actually_received;
	}
	player_name = std::string(buffer + 1);
	flag = player_name.size() > 0;
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