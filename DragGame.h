#pragma once

#include<vector>

#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class DragGame
{
public:
    DragGame(const int width, const int height, std::vector<Image>& dropPic,
        std::vector<Image>& dragPic);

    void start();

private:
    std::vector<Image> dragPic, dropPic;

    sf::Texture fileBG;

    const int additionalSpace = 200;
    sf::Sprite background;
    sf::RenderWindow window;
};
