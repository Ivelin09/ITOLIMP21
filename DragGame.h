#pragma once

#include "Window.h"
#include <SFML/Graphics.hpp>

#include "Images.h"
#include<vector>

extern const int width;
extern const int height;

class Singleton;

class DragGame
{
public:
    DragGame(sf::RenderWindow& window, std::vector<Image>& dragPic, std::vector<Image>& dropPic) : window(window), dropPic(dropPic), dragPic(dragPic), saveIndex(-1)
    {
        double substractedWidth = width - (dragPic[0].getShape().getSize().x * dragPic.size());
        double deltaWidth = substractedWidth / (dragPic.size() * 2);

        const int additionalSpace = 120;

        double currPos = 0;
        for (int i = 0; i < dragPic.size(); i++)
        {
            currPos += deltaWidth;
            this->dragPic[i].getShape().setPosition(currPos, height / 2 - (dragPic[i].getShape().getSize().y / 2) - additionalSpace);

            currPos += deltaWidth + dragPic[i].getShape().getSize().x;
        }

        currPos = 0;

        for (int i = 0; i < dropPic.size(); i++)
        {
            currPos += deltaWidth;
            this->dropPic[i].getShape().setPosition(currPos, height / 2 - (dropPic[i].getShape().getSize().y / 2) + additionalSpace);

            currPos += deltaWidth + dropPic[i].getShape().getSize().x;
        }
        file.loadFromFile(ImagePath + "DigitBg.jpg");
        background.setTexture(file);
    }

    void start()
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
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed) {

                    const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (int i = 0; i < dragPic.size(); i++) {
                        sf::Vector2f size = dragPic[i].getShape().getSize();
                        sf::Vector2f position = dragPic[i].getShape().getPosition();

                        if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                            mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
                            this->saveIndex = i;
                            movingObj = &this->dragPic[i];

                            back = movingObj->getShape().getPosition();
                            hold = true;
                        }
                        oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    }
                }
                else if (hold && event.type == sf::Event::MouseMoved) {

                    const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    sf::Vector2f cornerX = movingObj->getShape().getPosition();
                    sf::Vector2f cornerY = sf::Vector2f(movingObj->getShape().getPosition().x + movingObj->getShape().getSize().x,
                        movingObj->getShape().getPosition().y + movingObj->getShape().getSize().y);


                    movingObj->getShape().setPosition(movingObj->getShape().getPosition().x - oldPos.x + mouseCords.x, movingObj->getShape().getPosition().y - oldPos.y + mouseCords.y);
                    for (int w = 0; w < this->dragPic.size(); w++)
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
                                
                                movingObj->getShape().setPosition(back);

                                hold = false;
                            }
                        }
                    }
                    oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    hold = false;
                    movingObj = nullptr;
                }
            }

            window.clear();

            window.draw(this->background);

            window.draw(Singleton::get().backArrow.getShape());
            window.draw(Singleton::get().nextArrow.getShape());

            for (int i = 0; i < this->dragPic.size(); i++)
                window.draw(this->dragPic[i].getShape());

            for (int i = 0; i < dropPic.size(); i++)
                window.draw(dropPic[i].getShape());

            window.display();
        }

    }

    ~DragGame()
    {
        std::cout << "call\n";
    }

private:
    int saveIndex;
    std::vector<Image> dropPic, dragPic;

    sf::RenderWindow& window;

    sf::Texture file;
    sf::Sprite background;
};
