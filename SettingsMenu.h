#ifndef _SETTINGS_MENU_H_
#define _SETTINGS_MENU_H_

#include "MenuState.h"
#include "Button.h"
#include "TextField.h"

class SettingsMenu 
	: public MenuState
{
public:
	SettingsMenu(MenuScreen* menuScreen);
	~SettingsMenu();

	virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
	virtual void render(sf::RenderWindow* window) override;

private:
	TextField* textField;

	Button* okButton;
	Button* backButton;
};
#endif
