#ifndef _CREATE_ROOM_MENU_H_
#define _CREATE_ROOM_MENU_H_
#include "MenuState.h"
#include "TextField.h"
class CreateRoomMenu :
    public MenuState
{
public: 
    CreateRoomMenu(MenuScreen* menuScreen);
    ~CreateRoomMenu();
    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

private: 
    TextField* textField;

    Button* okButton;
    Button* backButton;

    std::string name_room;
};
#endif
