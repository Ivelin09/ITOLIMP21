#include<iostream>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Images.h"
#include "DragGame.h"

#include<vector>
#include<utility>

sf::RenderWindow window(sf::VideoMode(width, height), "Play with me!");

const int width = 1640;
const int height = 640;

class Singleton
{
public:
	static Singleton& get()
	{
		return obj;
	}

	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

	 sf::SoundBuffer correctSound, incorrectSound;
	 sf::Sound correct, incorrect;

	 Image zero, one, two, three, four, five, six, seven, eight, nine;
	 Image zeroPlace, onePlace, twoPlace, threePlace;

	 std::vector<Image> dragPic, dropPic;
	 std::vector<std::pair<sf::RectangleShape, DragGame*>> digits;
private:
	Singleton()
	{
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

		//BUTTONS

		sf::RectangleShape button(sf::Vector2f(100, 100));
		button.setPosition(sf::Vector2f(window.getSize().x / 2,
			window.getSize().y/2));

		// Digit Game Level 1

		dragPic.push_back(zero);
		dragPic.push_back(one);
		dragPic.push_back(two);
		dragPic.push_back(three);

		dropPic.push_back(zeroPlace);
		dropPic.push_back(onePlace);
		dropPic.push_back(twoPlace);
		dropPic.push_back(threePlace);

		DragGame* GameLevel1 = new DragGame(window, dragPic, dropPic);
		digits.push_back({ button, GameLevel1 });

		dragPic.clear();
		dropPic.clear();
	}

	~Singleton()
	{

	}

	static Singleton obj;
};

Singleton Singleton::obj;

int main()
{
	sf::Texture file;
	sf::Sprite bg;

	const Singleton& obj = Singleton::get();

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

		for (const auto& k : obj.digits)
			window.draw(k.first);

		window.display();
	}
}
