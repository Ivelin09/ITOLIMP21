#include <iostream>
#include <SFML/Graphics.hpp>

#include "Images.h"
#include "DragGame.h"

#include<vector>
#include<utility>

#include "Images.h"

sf::RenderWindow window(sf::VideoMode(width, height), "Play with me!");

const int width = 1640;
const int height = 640;

#include "Singleton.h"
const Singleton& obj = Singleton::get();


int main()
{
	sf::Texture file;
	sf::Sprite bg;

	file.loadFromFile(ImagePath + "DigitBG.jpg");
	bg.setTexture(file);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::MouseButtonPressed)
			{
				const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				for (int i = 0; i < obj.digits.size(); i++) 
				{
					auto objCords = obj.digits[i].first.getPosition();
					auto objSize = obj.digits[i].first.getSize();

					if (mouseCords.x >= objCords.x && mouseCords.x <= objCords.x + objSize.x &&
						mouseCords.y >= objCords.y && mouseCords.y <= objCords.y + objSize.y)
					{
						obj.digits[i].second->start();
					}
				}
			}
		}

		window.clear();
		window.draw(bg);

		window.draw(obj.get().zero.getShape());

		for (const auto& k : obj.digits)
			window.draw(k.first);

		window.display();
	}

	for (int i = 0; i < obj.digits.size(); i++)
		delete obj.digits[i].second;
}
