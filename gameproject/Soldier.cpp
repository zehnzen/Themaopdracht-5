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

void Soldier::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
	//for (int i = 0; i < walklimit; i++) {
	// vakjes tekenen
	// Terrain.changeColor(sf::Color::Green);
	//}
}
