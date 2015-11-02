//File Bomber.cpp

#include <SFML/Graphics.hpp>
#include "Bomber.h"

Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) :
	Unit{ id, textures, pos, color, scale }
{
	hitpoints = 150;
	attackpoints = 50;
	walklimit = 3;
	attackrange = 4;
	resetTurn();

	unitName = "Bomber";
	numFrames = 5;
}
