//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

Terrain::Terrain(){
	sprite.setPosition(sf::Vector2f{ 200,200 });
}

void Terrain::setText(sf::Texture & text) {
	sprite.setTexture(text);
}

void Terrain::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}