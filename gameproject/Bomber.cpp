//File Bomber.cpp

#include <SFML/Graphics.hpp>
#include "Bomber.h"

Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	hp = 150;
	dp = 50;
	walklimit = 3;

	numFrames = 5;
}

void Bomber::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
	//for (int i = 0; i < walklimit; i++) {
	// vakjes tekenen
	// Terrain.changeColor(sf::Color::Green);
	//}
}
