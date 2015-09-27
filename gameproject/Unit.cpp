//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"

Unit::Unit() {
	sprite.setPosition(sf::Vector2f{ 200,200 });
}

void Unit::setTexture(sf::Texture & text) {
	sprite.setTexture(text, true);
	sprite.setTextureRect((sf::IntRect(0, 0, 40, 40)));
}

void Unit::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Unit::draw(sf::RenderWindow & window, sf::Vector2f position) {		// draw methode met position erbij
	sprite.setPosition(position);
	window.draw(sprite);
}

void Unit::handleMouse(sf::Vector2f pos) {
	if (selected) { // als al geselecteerd dan afhandelen of hij wil lopen of toch wil afbreken)
		if () {	// checken of actie binnen zijn bereik valt
			// lopen
		}
		else {
			selected = false;
		}
	}
	else {		// als niet geselecteerd kijken of je hem alsnog wilt selecteren
		selected = sprite.getGlobalBounds().contains(pos);
	}
}

void Unit::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
}
