#pragma once

#include "Images.h"
#include<vector>

class DragGame;
extern sf::RenderWindow window;

class Singleton
{
public:
	static Singleton& get();

	Singleton();

	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

	sf::SoundBuffer correctSound, incorrectSound;
	sf::Sound correct, incorrect;

	Image zero, one, two, three, four, five, six, seven, eight, nine;
	Image zeroPlace, onePlace, twoPlace, threePlace;

	Image backArrow, nextArrow;

	std::vector<Image> dragPic, dropPic;
	std::vector<std::pair<sf::RectangleShape, DragGame*>> digits;
private:

	static Singleton obj;
};
