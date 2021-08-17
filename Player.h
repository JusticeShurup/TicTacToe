#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SFML/Graphics.hpp>
#include <Poco/Net/StreamSocket.h>

class Player
{
public:
	Player(int number);
	int getNumber();
	void setConnection(std::string address);
	Poco::Net::StreamSocket getSock();
private:
	int number;
	Poco::Net::StreamSocket client;
};
#endif