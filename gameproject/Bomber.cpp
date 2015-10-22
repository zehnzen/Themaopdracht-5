//File Bomber.cpp

#include <SFML/Graphics.hpp>
#include "Bomber.h"

Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	setPos(pos);
	sprite.setColor(color);
	Unit::walklimit = walklimit;
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
