//File Soldier.cpp

#include <SFML/Graphics.hpp>
#include "Soldier.h"

Soldier::Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) :
	Unit{ id, textures, pos, color, scale }
{
	hitpoints = 80;
	attackpoints = 30;
	walklimit = 3;
	attackrange = 4;
	resetTurn();

	unitName = "Soldier";
	numFrames = 6;
}
