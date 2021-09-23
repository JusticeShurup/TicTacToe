#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Server.h"

class Game;
class Player;

class Screen
{
protected:
	
	Game* game;
	Server* server;

public:
	
	void setGame(Game* game);
	void setServer(Server* server);

	void setScreen(Screen* screen);

	void sendNameBytes(char(&buffer)[18]);
	void receiveNameBytes(char(&buffer)[18]);

	Game* getGame();
	Server* getServer();

	Player* getPlayer();

	virtual ~Screen() {};

	virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) = 0;
	virtual void processLogic(float delta_time, sf::RenderWindow* window) = 0;
	virtual void render(sf::RenderWindow* window) = 0;


};
#endif

