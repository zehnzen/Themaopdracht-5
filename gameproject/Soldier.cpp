//File Soldier.cpp

#include <SFML/Graphics.hpp>
#include "Soldier.h"

Soldier::Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	hitpoints = 100;
	attackpoints = 10;
	walklimit = 1;
	sprite.setColor(color);
	unitName = "Soldier";

	numFrames = 5;
	repeat = true;
}