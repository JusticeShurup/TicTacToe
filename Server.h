#ifndef _SERVER_H_
#define _SERVER_H_
#include "Poco/Net/StreamSocket.h"
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
#include <atomic>

class Server
{
public: 
	Server(Poco::Net::StreamSocket& client);
	
	void NetEvent();

	std::string getSecondPlayerNickname() const;

	bool isNicknameRecieved();

	void run();

	void close();
private:
	char buffer[18];
	Poco::Net::StreamSocket client;
	Poco::RunnableAdapter<Server> adapter;
	Poco::Thread thread;
	uint8_t size;
	std::string player_name;
	std::atomic<bool> flag;
};
#endif
