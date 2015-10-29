//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

Terrain::Terrain(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	sprite.setColor(sf::Color::White);
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
}

void Terrain::changeColor(sf::Color col) {
	sprite.setColor(col);
}