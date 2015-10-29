//File Building.cpp

#include "Building.h"

Building::Building(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	PlayerObject(id, textures, pos, color)
{
	setPosition(pos);

	numFrames = 1;
}