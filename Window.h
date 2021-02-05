#pragma once
#include "Images.h"

class Window
{
public:

    Window(const int width, const int height, std::vector<Image>& buttons, const std::string& bg);

    Image* isClicked(const sf::RenderWindow& window);

protected:
    std::vector<Image> buttons;
    sf::RenderWindow window;

    sf::Sprite background;
    sf::Texture bg;

    int saveIndex;
};
