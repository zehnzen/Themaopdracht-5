//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

Terrain::Terrain(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	sprite.setColor(sf::Color::White);
}

void Terrain::changeColor(sf::Color col) {
	sprite.setColor(col);
}