#pragma once

#include<string>
#include<vector>

#include<SFML/Graphics.hpp>
#include "Images.h"

class Window
{
public:

    Window(const int width, const int height, const std::string& path);

    virtual Window* start();

protected:
    sf::RenderWindow window;
    sf::Sprite background;

    sf::Texture backgroundFile;
    std::vector<Image> buttons;
};
