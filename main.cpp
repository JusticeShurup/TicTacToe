#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "Game.h"

using namespace sf;

int main()
{
    RenderWindow menu(VideoMode(450, 450), "Menu");
    RectangleShape playButton(Vector2f(450, 100));
    RectangleShape exitButton(Vector2f(450, 100));
    Font font;
    font.loadFromFile("Inconsolata_Condensed-Bold.ttf");
    Text playButtonText;
    Text exitButtonText;

    playButtonText.setFont(font);
    playButtonText.setCharacterSize(75);
    playButtonText.setString("Play");
    playButtonText.setPosition(175, 0);
    playButtonText.setFillColor(Color::Black);

    exitButtonText.setFont(font);
    exitButtonText.setCharacterSize(75);
    exitButtonText.setString("Exit");
    exitButtonText.setPosition(175, 350);
    exitButtonText.setFillColor(Color::Black);


    playButton.setPosition(0, 0);
    exitButton.setPosition(0, 350);
    while (menu.isOpen()) {
        Event event;

        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                menu.close();
        }

        menu.clear();
        menu.draw(playButton);
        menu.draw(playButtonText);
        menu.draw(exitButton);
        menu.draw(exitButtonText);
        menu.display();

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (playButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition(menu)))){

                menu.close();
                Game game(Vector2f(150, 150), 0);
                game.run();
          
            }
            else if (exitButton.getGlobalBounds().contains(Vector2f(Mouse::getPosition(menu)))) {

                menu.close();

            }
        }

    }


    return 0;
}