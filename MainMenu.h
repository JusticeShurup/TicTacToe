#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_
#include "MenuState.h"
#include "Button.h"

class MainMenu :
    public MenuState
{
public: 
    MainMenu(MenuScreen* menuScreen);
    ~MainMenu();

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;
private:
    Button* playButton;
    Button* settingsButton;

    Button* exitButton;
};
#endif

