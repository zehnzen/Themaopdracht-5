//File Bomber.cpp

#include <SFML/Graphics.hpp>
#include "Bomber.h"

Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	setPos(pos);
	sprite.setColor(color);

	frameSize = sf::Vector2i(50,50);
	numFrames = 5;
	currentFrame = 0;
	duration = sf::seconds(1);
	elapsedTime = sf::Time::Zero;
	repeat = true;
}

void Bomber::update(sf::Time dt) {
	sf::Time timePerFrame = duration / (float)numFrames;
	elapsedTime += dt;

	sf::Vector2i textureBounds(sprite.getTexture()->getSize());
	sf::IntRect textureRect = sprite.getTextureRect();

	if (currentFrame == 0) {
		textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
	}

	while (elapsedTime >= timePerFrame && (currentFrame <= numFrames || repeat))
	{
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}
		elapsedTime -= timePerFrame;
		if (repeat) {
			currentFrame = (currentFrame + 1) % numFrames;
			if (currentFrame == 0)
				textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
		}
		else
		{
			currentFrame++;
		}
	}
	sprite.setTextureRect(textureRect);
}

void Bomber::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
	//for (int i = 0; i < walklimit; i++) {
	// vakjes tekenen
	// Terrain.changeColor(sf::Color::Green);
	//}
}

int Bomber::getHP() {
	return hp;
}

int Bomber::getDP() {
	return dp;
}

int Bomber::getWalklimit() {
	return walklimit;
}
