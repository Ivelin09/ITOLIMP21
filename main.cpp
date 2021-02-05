#include <SFML/Graphics.hpp>
#include<iostream>

#include<vector>
#include "Images.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

const int width = 1024, height = 768;

enum WINDOW_TYPE {DigitGame, CLOSED};

int main() {
    initializeImages();

    sf::RenderWindow window(sf::VideoMode(1920, 1200), "Play with me!");

    sf::Texture bg, button;
    bg.loadFromFile(ImagePath + "menuBg.jpg");
    button.loadFromFile(ImagePath + "buttonDigits.png");

    sf::Sprite background;
    background.setTexture(bg);

    int additionalSpace = 150;

    sf::RectangleShape digitButton(sf::Vector2f(500, 210));
    digitButton.setPosition(1920 / 2 - digitButton.getSize().x / 2, 1200 / 2 - digitButton.getSize().y / 2 - additionalSpace);

    std::vector<std::pair< WINDOW_TYPE , sf::RectangleShape>> buttons;
    buttons.emplace_back(DigitGame, digitButton);

    digitButton.setTexture(&button);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                for (int i = 0; i < buttons.size(); i++) {
                    if (mouseCords.x >= buttons[i].second.getPosition().x &&
                        mouseCords.x <= buttons[i].second.getPosition().x + buttons[i].second.getSize().x &&
                        mouseCords.y >= buttons[i].second.getPosition().y &&
                        mouseCords.y <= buttons[i].second.getPosition().y + buttons[i].second.getSize().y)
                    {
                        if (buttons[i].first == DigitGame)
                        {

                        }
                    }
                }
            }
        }

        window.clear();

        window.draw(background);
        for (int i = 0; i < buttons.size(); i++)
            window.draw(buttons[i].second);

        window.display();
    }
    (std::cout << "text" << std::endl);
    return 0;
}
