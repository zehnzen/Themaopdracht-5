//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

Terrain::Terrain(){
	sprite.setPosition(sf::Vector2f{ 200,200 });
}

void Terrain::setTexture(sf::Texture & text) {
	sprite.setTexture(text, true);
	sprite.setTextureRect(sf::IntRect{ 0,0,30,30 });
}

void Terrain::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Terrain::draw(sf::RenderWindow & window, sf::Vector2f position) {		// draw methode met position erbij
	sprite.setPosition(position);
	sprite.setTextureRect((sf::IntRect(0, 0, 40, 40)));
	window.draw(sprite);
}