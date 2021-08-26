#ifndef _LOBBY_MENU_H_
#define _LOBBY_MENU_H_
#include "MenuState.h"
class LobbyMenu :
    public MenuState
{
public:
	LobbyMenu(MenuScreen* menuScreen);
	~LobbyMenu();

	std::string receiveGameName();
	void initPlayer2(std::string nickname);

	virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
	virtual void render(sf::RenderWindow* window) override;

private:

	char buffer[20];
	Button* readyButton;
	Button* exitButton;


	sf::Font font;
	sf::Text* game_name;
	sf::Text* player1_nickname;
	sf::Text* player2_nickname;
};
#endif
