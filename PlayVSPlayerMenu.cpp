#include "PlayVSPlayerMenu.h"
#include "PlayMenu.h"
#include "MenuScreen.h"
#include "CreateRoomMenu.h"
#include "FindRoomMenu.h"
#include "Game.h"
#include <Poco/Net/StreamSocket.h>


using namespace sf;


PlayVSPlayerMenu::PlayVSPlayerMenu(MenuScreen* menuScreen) {
	setMenuScreen(menuScreen);
	std::string player_nickname;
	std::cin >> player_nickname;
	menuScreen->getPlayer()->setNickname(player_nickname);
	createRoomButton = new Button(550, 100, 0, 0, "Create room");
	findRoomButton = new Button(550, 100, 0, 100, "Find room");
	backButton = new Button(550, 100, 0, 350, "Back");
}

PlayVSPlayerMenu::~PlayVSPlayerMenu() {
	delete createRoomButton;
	delete findRoomButton;
	delete backButton;
}

void PlayVSPlayerMenu::handleEvent(Event& event, RenderWindow* window) {
	createRoomButton->update(Vector2f(Mouse::getPosition(*window)), event);
	findRoomButton->update(Vector2f(Mouse::getPosition(*window)), event);
	backButton->update(Vector2f(Mouse::getPosition(*window)), event);

	if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
        if (createRoomButton->isClicked()) {
			uint8_t message = 1;
			uint8_t player_name_size = menuScreen->getGame()->getPlayer()->getNickame().size();
			std::string player_name(menuScreen->getPlayer()->getNickame());
			menuScreen->getPlayer()->setConnection("127.0.0.1:1337");
			menuScreen->setServer(new Server(menuScreen->getPlayer()->getSock()));
			menuScreen->getPlayer()->getSock().sendBytes(&player_name_size, sizeof(player_name_size));
			menuScreen->getPlayer()->getSock().sendBytes(player_name.c_str(), player_name.size());
			menuScreen->getPlayer()->getSock().sendBytes(&message, sizeof(uint8_t));
			menuScreen->state->setNewState(new CreateRoomMenu(menuScreen));
        }
		else if (findRoomButton->isClicked()) {
			uint8_t message = 2;
			uint8_t player_name_size = menuScreen->getGame()->getPlayer()->getNickame().size();
			std::string player_name(menuScreen->getPlayer()->getNickame());
			menuScreen->getPlayer()->setConnection("127.0.0.1:1337");
			menuScreen->setServer(new Server(menuScreen->getGame()->getPlayer()->getSock()));
			menuScreen->getPlayer()->getSock().sendBytes(&player_name_size, sizeof(player_name_size));
			menuScreen->getPlayer()->getSock().sendBytes(player_name.c_str(), player_name.size());
			menuScreen->getPlayer()->getSock().sendBytes(&message, sizeof(uint8_t));
			menuScreen->state->setNewState(new FindRoomMenu(menuScreen));
		}
        else if (backButton->isClicked()) {
			menuScreen->state->setNewState(new PlayMenu(menuScreen));
        }
	}
}

void PlayVSPlayerMenu::render(RenderWindow* window) {
	window->clear();
	createRoomButton->render(window);
	findRoomButton->render(window);
	backButton->render(window);
	window->display();
}