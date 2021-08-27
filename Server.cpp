#include "Server.h"
#include <functional>
#include <thread>
#include <string>

Server::Server(Poco::Net::StreamSocket& client) :
	client(client),
	flag(false),
	buffer{0}
{}

void Server::NetEvent() {
	client.receiveBytes(buffer, 20);
	strcpy(buffer[0], player_name.c_str());
	std::cout << player_name << std::endl;
}

void Server::run() {
	Poco::RunnableAdapter<Server> adapter(*this, &Server::NetEvent);
	thread.start(adapter);
}

void Server::close() {
	thread.join();
}