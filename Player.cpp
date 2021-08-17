#include "Player.h"
#include "Poco/Net/SocketAddress.h"
Player::Player(int number) : number(number) {}

int Player::getNumber() {
	return number;
}

void Player::setConnection(std::string address) {
	Poco::Net::SocketAddress address_server(address);
	client.connect(address_server);
}

Poco::Net::StreamSocket Player::getSock() {
	return client;
}

