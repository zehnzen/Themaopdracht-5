//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

Terrain::Terrain(textureID id, const textureHolder & textures) :
	id{ id },
	sprite{textures.get(id) }
{
	sprite.setColor(sf::Color::White);
}

Terrain::Terrain(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	id{ id },
	sprite{ textures.get(id), sf::IntRect{0,0,TILESIZE,TILESIZE} }
{
	sprite.setColor(sf::Color::White);
	sprite.setPosition(pos);
}

/*
void Terrain::setTexture(sf::Texture & text) {
	sprite.setTexture(text, true);
	sprite.setTextureRect(sf::IntRect{ 0,0,30,30 });
}*/

void Terrain::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Terrain::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}


void Terrain::changeColor(sf::Color col) {
	sprite.setColor(col);
}