#include <SFML/Graphics.hpp>
#include<iostream>

#include<vector>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

#include "Window.h"
#include "Images.h"

const int width = 1024, height = 768;

class DragGame : public Window
{
public:
    DragGame() : Window(width, height, "DigitBG.jpg") {}
    virtual Window* start() override
    {
        Image* movingObj = nullptr;

        sf::Vector2f back;
        bool hold = false;

        sf::Vector2f oldPos;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {

                    const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (int i = 0; i < buttons.size(); i++) {
                        sf::Vector2f size = buttons[i].getShape().getSize();
                        sf::Vector2f position = buttons[i].getShape().getPosition();

                        if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                            mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
                            this->saveIndex = i;
                            movingObj = &this->buttons[i];
                        }
                    }
                }
                else if (hold && event.type == sf::Event::MouseMoved) {

                    const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    sf::Vector2f cornerX = movingObj->getShape().getPosition();
                    sf::Vector2f cornerY = sf::Vector2f(movingObj->getShape().getPosition().x + movingObj->getShape().getSize().x,
                        movingObj->getShape().getPosition().y + movingObj->getShape().getSize().y);


                    movingObj->getShape().setPosition(movingObj->getShape().getPosition().x - oldPos.x + mouseCords.x, movingObj->getShape().getPosition().y - oldPos.y + mouseCords.y);
                    for (int w = 0; w < this->buttons.size(); w++)
                    {
                        sf::Vector2u size1(movingObj->getShape().getSize().x, movingObj->getShape().getSize().y);
                        sf::Vector2f position1 = dropPic[w].getShape().getPosition();


                        if ((cornerX.x >= position1.x &&
                            cornerX.x <= position1.x + size1.x && cornerX.y >= position1.y && cornerX.y <= position1.y + size1.y) ||
                            (cornerY.x >= position1.x && cornerY.x <= position1.x + size1.x && cornerY.y >= position1.y && cornerY.y <= position1.y + size1.y) ||
                            (cornerX.x >= position1.x && cornerX.x <= position1.x + size1.x && cornerY.y >= position1.y && cornerY.y <= position1.y + size1.y) ||
                            (cornerY.x >= position1.x && cornerY.x <= position1.x + size1.x && cornerX.y >= position1.y && cornerX.y <= position1.y + size1.y))
                        {
                            if (this->saveIndex == w) {
                                movingObj->play();
                                movingObj->getShape().setPosition(dropPic[w].getShape().getPosition());
                            }
                            else {
                                //incorrect.play();
                                movingObj->getShape().setPosition(back);

                                hold = false;
                            }
                        }
                    }
                    oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
            }

            this->window.clear();
            this->window.draw(this->background);

            for (int i = 0; i < dropPic.size(); i++)
                this->window.draw(dropPic[i].getShape());

            for (int i = 0; i < this->buttons.size(); i++)
                this->window.draw(this->buttons[i].getShape());

            window.display();
        }

        return nextWindow();
    }
    ~DragGame()
    {
        std::cout << "call\n";
    }
    virtual void play()
    {

    }

    virtual Window* nextWindow()
    {
        return nullptr;
    }

private:
    int saveIndex;
    std::vector<Image> dropPic;
};
Window* ptr;

int main() {

    ptr = new DragGame;
    Window* save = nullptr;

    while (ptr)
    {
        save = ptr;
        ptr = ptr->start();

        delete save;
    }

    return 0;
}















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

private:
    sf::Texture texture;
    sf::RectangleShape shape;

    sf::SoundBuffer sound;
    sf::Sound player;
};

sf::SoundBuffer correctSound, incorrectSound;
sf::Sound correct, incorrect;

Image zero, one, two, three, four, five, six, seven, eight, nine;
Image zeroPlace, onePlace, twoPlace, threePlace;

void initializeImages()
{
    // IMAGES

    zero.setTexture("zero.png");

    zero.getShape().getTexture()->getSize();

    zeroPlace.setTexture("zeroPlace.png");

    zero.setSound("zero.wav");

    one.setTexture("one.png");
    onePlace.setTexture("onePlace.png");

    one.setSound("one.wav");

    two.setTexture("two.png");
    twoPlace.setTexture("twoPlace.png");

    two.setSound("two.wav");

    three.setTexture("three.png");
    threePlace.setTexture("threePlace.png");

    three.setSound("three.wav");

    // Audio
    correctSound.loadFromFile(AudioPath + "correct.wav");
    correct.setBuffer(correctSound);

    incorrectSound.loadFromFile(AudioPath + "incorrect.wav");
    incorrect.setBuffer(incorrectSound);

}


