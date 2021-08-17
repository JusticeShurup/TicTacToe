#ifndef _PLAY_VS_PLAYER_MENU_H_
#define _PLAY_VS_PLAYER_MENU_H_
#include "MenuState.h"
class PlayVSPlayerMenu :
    public MenuState
{
public: 
    PlayVSPlayerMenu(MenuScreen* menuScreen);
    ~PlayVSPlayerMenu();

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

private: 
    Button* findRoomButton;
    Button* createRoomButton;

    Button* backButton;
};
#endif

