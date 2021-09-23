#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#include "Screen.h"
#include "GameShape.h"
class GameScreen :
    public Screen
{
public:
    
    GameScreen(Game* game);

    void update(int player_number, sf::Event& event);

    bool checkWin(int player_number);
    void setClick(float X, float Y, int player_number);

    void undoClick();

    void simulateAI(int AI_number);

    virtual void handleEvent(sf::Event& event, sf::RenderWindow* window) override;
    virtual void processLogic(float delta_time, sf::RenderWindow* window) override;
    virtual void render(sf::RenderWindow* window) override;
private: 

    sf::Image* claimTurnImage;
    sf::Texture* claimTurnTexture;
    sf::RectangleShape* claimTurnButton;
    std::vector<sf::RectangleShape> shapes;
    std::vector<GameShape> gameShapes;
        
    int gameShape_number; // ������ ����� ��� �� �������������� �������� ��� ������ 
    int claimed_shapes[9];

    char buffer[9];

    bool claimTurn;

    uint8_t turn; // ���������� ������������ ��� ��� (false - ������ �����, true - ������ �����)
    bool vsAI; // ������ �� ������ ���� ��� ���
};
#endif

