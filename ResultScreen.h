#ifndef _RESULT_SCREEN_H_
#define _RESULT_SCREEN_H_
#include "Screen.h"
#include "Button.h"
class ResultScreen :
    public Screen
{
public: 
    ResultScreen(Game* game);
    ~ResultScreen();

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void processLogic(float delta_time, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;

private:
    Button* okButton;
    
};
#endif