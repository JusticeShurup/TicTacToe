#ifndef _FIND_ROOM_MENU_H_
#define _FIND_ROOM_MENU_H_
#include "MenuState.h"
#include "TextField.h"
class FindRoomMenu :
    public MenuState
{
    static const int MAX_NAME_LENGHT = 128;
public: 
    FindRoomMenu(MenuScreen* menuScreen);
    ~FindRoomMenu();

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

private:
    char name_buffer[MAX_NAME_LENGHT];
    TextField* textField;
    Button* okButton;
    std::string text;

    Button* backButton;

};
#endif

