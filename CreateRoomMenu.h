#ifndef _CREATE_ROOM_MENU_H_
#define _CREATE_ROOM_MENU_H_
#include "MenuState.h"
#include "TextField.h"
class CreateRoomMenu :
    public MenuState
{
    static const int MAX_NAME_LENGHT = 18;
public: 
    CreateRoomMenu(MenuScreen* menuScreen);
    ~CreateRoomMenu();
    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

private: 

    char name_buffer[MAX_NAME_LENGHT];
    TextField* textField;

    Button* okButton;
    Button* backButton;

    std::string name_room;
};
#endif
