#ifndef _PLAY_MENU_H_
#define _PLAY_MENU_H_
#include "MenuState.h"
class PlayMenu :
    public MenuState
{
public:
    PlayMenu(MenuScreen* menuScreen);
    ~PlayMenu();

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

private: 
    Button* playVSAIButton;
    Button* playVSPlayerButton;

    Button* backButton;
};
#endif
