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

sf::Color Terrain::getColor() {
	return sprite.getColor();
}

bool Terrain::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

bool Terrain::getFree() {
	return free;
}

void Terrain::setFree(bool f) {
	free = f;
}