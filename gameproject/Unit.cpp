//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"
#include "Terrain.h"


Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	id{ id },
	sprite{ textures.get(id), sf::IntRect(0, 0, TILESIZE - 10, TILESIZE - 10) },
	side {color}
{
	setPos(pos);
	sprite.setColor(color);
}

void Unit::setTexture(sf::Texture & text) {
	sprite.setTexture(text, true);
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE - 10, TILESIZE - 10));
}

void Unit::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos.x + 7, pos.y + 7);
}

void Unit::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Unit::handleMouse(sf::Vector2f pos) {
	if (selected) { // als al geselecteerd dan afhandelen of hij wil lopen of toch wil afbreken)
		sprite.setColor(sf::Color::Yellow);
		if ((pos.x - sprite.getPosition().x >= -TILESIZE * walklimit)	&& (pos.x - sprite.getPosition().x <= 0) && ((pos.y - sprite.getPosition().y <= TILESIZE ) && (pos.y - sprite.getPosition().y >= 0))) {		// rechts
				setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));
		}
		else if ((pos.x - sprite.getPosition().x <= TILESIZE * walklimit + TILESIZE) && (pos.x - sprite.getPosition().x >= 0) && ((pos.y - sprite.getPosition().y <= TILESIZE) && (pos.y - sprite.getPosition().y >= 0))) {		// links
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));
		}
		else if ((pos.y - sprite.getPosition().y >= -TILESIZE * walklimit) && (pos.y - sprite.getPosition().y <= 0) && ((pos.x - sprite.getPosition().x <= TILESIZE) && (pos.x - sprite.getPosition().x >= 0))) {		// omhoog
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));
		}
		else if ((pos.y - sprite.getPosition().y <= TILESIZE * walklimit + TILESIZE) && (pos.y - sprite.getPosition().y >= 0) && ((pos.x - sprite.getPosition().x <= TILESIZE) && (pos.x - sprite.getPosition().x >= 0))) {		// omlaag
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));
		}

		selected = false;
		sprite.setColor(side);
	}
	else {		// als niet geselecteerd kijken of je hem alsnog wilt selecteren
		setSelected(sprite.getGlobalBounds().contains(pos));
	}
}

void Unit::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
	//for (int i = 0; i < walklimit; i++) {
		// vakjes tekenen
		// Terrain.changeColor(sf::Color::Green);
	//}
}

void Unit::setSelected(bool sel) {
	selected = sel;
	if (selected) {
		sprite.setColor(sf::Color::Yellow);
	}
	else {
		sprite.setColor(side);
	}
}

bool Unit::getSelected() {
	return selected;
}
