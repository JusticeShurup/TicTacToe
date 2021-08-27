#include "Player.h"
#include "Poco/Net/SocketAddress.h"
Player::Player(int number) : number(number) {}

Player::~Player() {
	client.close();
}

void Player::setNickname(std::string nickame) {
	this->nickname = nickame;
}

std::string Player::getNickame() const{
	return nickname;
}

int Player::getNumber() {
	return number;
}

void Player::setConnection(std::string address) {
	Poco::Net::SocketAddress address_server(address);
	client.connect(address_server);
}

Poco::Net::StreamSocket& Player::getSock(){
	return client;
}

