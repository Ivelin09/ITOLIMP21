#pragma once

#include<SFML/Graphics.hpp>
#include<string>

#include<SFML/Audio.hpp>
#include<iostream>

#include "DragGame.h"

const std::string ImagePath = "C:/Users/Ivo/source/repos/ConsoleApplication163/ConsoleApplication163/Content/";
const std::string AudioPath = "C:/Users/Ivo/source/repos/ConsoleApplication163/ConsoleApplication163/Sound/";


class Image
{
public:
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


void initializeWindows()
{
	
};

void initializeImages()
{
	// IMAGES
	const int width = 160, height = 160;

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
