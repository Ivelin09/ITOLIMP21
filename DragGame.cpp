#include "DragGame.h"

DragGame::DragGame(const int width, const int height, std::vector<Image>& dropPic,
    std::vector<Image>& dragPic) : Window(width, height, dragPic, "DigitBG.jpg"), dropPic(dropPic)
{
    double substractedWidth = width - (dragPic[0].getShape().getSize().x * dragPic.size());
    double deltaWidth = substractedWidth / (dragPic.size() * 2);

    double currPos = 0;
    for (int i = 0; i < dragPic.size(); i++)
    {
        currPos += deltaWidth;
        this->buttons[i].getShape().setPosition(currPos, height / 2 - (dragPic[i].getShape().getSize().y / 2) - additionalSpace);

        currPos += deltaWidth + dragPic[i].getShape().getSize().x;
    }

    currPos = 0;

    for (int i = 0; i < dropPic.size(); i++)
    {
        currPos += deltaWidth;
        this->dropPic[i].getShape().setPosition(currPos, height / 2 - (dropPic[i].getShape().getSize().y / 2) + additionalSpace);

        currPos += deltaWidth + dropPic[i].getShape().getSize().x;
    }
    fileBG.loadFromFile("DigitBg.jpg");

    background.setTexture(fileBG);
}

void DragGame::start()
{
    Image* movingObj = nullptr;

    sf::Vector2f back;
    bool hold = false;

    sf::Vector2f oldPos;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::EventType::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {

                const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < dragPic.size(); i++) {
                    sf::Vector2f size = dragPic[i].getSize();
                    sf::Vector2f position = dragPic[i].getPosition();

                    if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                        mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
                        saveIndex = i;
                        hold = true;
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
                        if (saveIndex == w) {
                            movingObj->play();
                            movingObj->getShape().setPosition(dropPic[w].getShape().getPosition());
                        }
                        else {
                            incorrect.play();
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

        // std::cout << dropPic[1].getShape().getPosition().x << std::endl;

        for (int i = 0; i < dropPic.size(); i++)
            window.draw(dropPic[i].getShape());

        for (int i = 0; i < this->buttons.size(); i++)
            window.draw(this->buttons[i].getShape());

        window.display();
    }
}
