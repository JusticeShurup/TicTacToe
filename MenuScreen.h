#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_
#include "Screen.h"
#include "TextField.h"
#include <vector>
#include "MenuState.h"

class MenuScreen :
    public Screen
{

public: 
    
    MenuScreen(Game* game);
    ~MenuScreen();

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void processLogic(float delta_time, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

    MenuState* state;
private:

};

#endif
