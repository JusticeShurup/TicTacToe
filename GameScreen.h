#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#include "Screen.h"
#include "GameShape.h"
class GameScreen :
    public Screen
{
public:
    
    GameScreen(Game* game);

    void update(Player* player, sf::Event& event);

    bool checkWin(int player);
    void setClick(float X, float Y, Player* player);

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
    std::vector<int> claimed_shapes;

    char buffer[18];

    bool claimTurn;

    bool turn; // ���������� ������������ ��� ��� (false - ������ �����, true - ������ �����)
    bool vsAI; // ������ �� ������ ���� ��� ���
};
#endif

