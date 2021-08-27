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

	void run();

	void close();
private:
	Poco::Net::StreamSocket client;
	char* buffer[20];
	Poco::Thread thread;
	std::string player_name;
	std::atomic<bool> flag;
};
#endif
