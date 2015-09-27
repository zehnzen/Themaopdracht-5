//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"

Unit::Unit() {
	sprite.setPosition(sf::Vector2f{ 200,200 });
}

void Unit::setText(sf::Texture & text) {
	sprite.setTexture(text);
}

void Unit::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Unit::draw(sf::RenderWindow & window, sf::Vector2f position) {		// draw methode met position erbij
	sprite.setPosition(position);
	sprite.setTextureRect((sf::IntRect(0, 0, 40, 40)));
	window.draw(sprite);
}