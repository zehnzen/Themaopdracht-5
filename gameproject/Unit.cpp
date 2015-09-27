//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"

Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	id{ id },
	sprite{ textures.get(id) }
{
	setPos(pos);
	sprite.setTextureRect((sf::IntRect(0, 0, 40, 40)));
}

void Unit::setTexture(sf::Texture & text) {
	sprite.setTexture(text, true);
	sprite.setTextureRect((sf::IntRect(0, 0, 40, 40)));
}

void Unit::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos.x + 7, pos.y + 7);
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
		if (pos.x <= 200) {	// checken of actie binnen zijn bereik valt
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), 50)));	//Lelijkste stukje code van allemaal, gaat zoveel afronding fout wss
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
