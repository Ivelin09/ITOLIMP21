#include "Singleton.h"

Singleton& Singleton::get()
{
	return obj;
}

Singleton::Singleton()
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
	// Audio

	zero.setSound("zero.wav");

	one.setSound("one.wav");

	two.setSound("two.wav");

	two.setSound("two.wav");

	three.setSound("three.wav");

	correctSound.loadFromFile(AudioPath + "correct.wav");
	correct.setBuffer(correctSound);

	incorrectSound.loadFromFile(AudioPath + "incorrect.wav");
	incorrect.setBuffer(incorrectSound);

	//BUTTONS

	std::cout << window.getSize().x << ' ' << window.getSize().y << std::endl;

	sf::RectangleShape button(sf::Vector2f(100, 100));
	button.setPosition(sf::Vector2f(window.getSize().x / 2,
		window.getSize().y / 2));

	backArrow.setTexture("backArrow.png");
	nextArrow.setTexture("nextArrow.png");

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

Singleton Singleton::obj;
