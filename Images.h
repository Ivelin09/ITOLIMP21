#ifndef IMAGES
#define IMAGES

#include<string>
#include<iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const std::string ImagePath = "C:/Users/Ivo/source/repos/ConsoleApplication163/ConsoleApplication163/Content/";
const std::string AudioPath = "C:/Users/Ivo/source/repos/ConsoleApplication163/ConsoleApplication163/Sound/";

class Image
{
public:

    Image()
    {

    }
    void play()
    {
        this->player.play();
    }

    void setTexture(const std::string& texture)
    {
        if (!this->texture.loadFromFile(ImagePath + texture))
            std::cout << "problem \n";
        shape.setTexture(&this->texture);
        shape.setSize(sf::Vector2f(200, 200));
    }

    void setSound(const std::string& sound)
    {
        this->sound.loadFromFile(AudioPath + sound);
        player.setBuffer(this->sound);
    }

    sf::RectangleShape& getShape()
    {
        return this->shape;
    }

    ~Image()
    {

    }

private:
    sf::Texture texture;
    sf::RectangleShape shape;

    sf::SoundBuffer sound;
    sf::Sound player;
};

#endif
