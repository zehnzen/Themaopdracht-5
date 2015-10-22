//File Soldier.cpp

#include <SFML/Graphics.hpp>
#include "Soldier.h"

Soldier::Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{id, textures, pos, color}
{
	setPos(pos);
	sprite.setColor(color);
	Unit::walklimit = walklimit;
}


int Soldier::getHP() {
	return hp;
}

int Soldier::getDP() {
	return dp;
}

int Soldier::getWalklimit() {
	return walklimit;
}
