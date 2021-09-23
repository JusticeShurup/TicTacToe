#include "Player.h"
#include "Poco/Net/SocketAddress.h"
#include <fstream>

Player::Player(int number) : 
	number(number), 
	nickname("Player")
{
	std::ifstream s("player_name.txt");
	char buff[18];
	if (s) {
		s.getline(buff, 18);
		nickname = buff;
	}
}

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

void Player::setNumber(int number) {
	this->number = number;
}

void Player::setConnection(std::string address) {
	Poco::Net::SocketAddress address_server(address);
	client.connect(address_server);
}

Poco::Net::StreamSocket& Player::getSock(){
	return client;
}

