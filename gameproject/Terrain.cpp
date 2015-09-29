//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

Terrain::Terrain(textureID id, const textureHolder & textures) :
	id{ id },
	sprite{textures.get(id) }
{}

Terrain::Terrain(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	id{ id },
	sprite{ textures.get(id), sf::IntRect{0,0,TILESIZE,TILESIZE} }
{
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

void Terrain::draw(sf::RenderWindow & window, sf::Vector2f position) {		// draw methode met position erbij
	sprite.setPosition(position);
	sprite.setTextureRect((sf::IntRect(0, 0, TILESIZE - 10, TILESIZE - 10)));
	window.draw(sprite);
}