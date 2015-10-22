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

sf::Vector2f Unit::getPosition() {
	return sprite.getPosition();
}

int Unit::getWalklimit() {
	return walklimit;
}

void Unit::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Unit::handleMouse(sf::Vector2f pos) {
	if (selected) { // als al geselecteerd dan afhandelen of hij wil lopen of toch wil afbreken)
		sprite.setColor(sf::Color::Yellow);

		if (checkWalk(pos)) {
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));
		}

		selected = false;
		sprite.setColor(side);
	}
	else {		// als niet geselecteerd kijken of je hem alsnog wilt selecteren
		setSelected(sprite.getGlobalBounds().contains(pos));
	}
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


bool Unit::checkWalk(sf::Vector2f pos) {
	bool b = false;

	if ((pos.x - sprite.getPosition().x >= -TILESIZE * walklimit) && (pos.x - sprite.getPosition().x <= 0) && ((pos.y - sprite.getPosition().y <= TILESIZE) && (pos.y - sprite.getPosition().y >= 0))) {		// rechts
		b = true;
	}
	else if ((pos.x - sprite.getPosition().x <= TILESIZE * walklimit + TILESIZE) && (pos.x - sprite.getPosition().x >= 0) && ((pos.y - sprite.getPosition().y <= TILESIZE) && (pos.y - sprite.getPosition().y >= 0))) {		// links
		b = true;
	}
	else if ((pos.y - sprite.getPosition().y >= -TILESIZE * walklimit) && (pos.y - sprite.getPosition().y <= 0) && ((pos.x - sprite.getPosition().x <= TILESIZE) && (pos.x - sprite.getPosition().x >= 0))) {		// omhoog
		b = true;
	}
	else if ((pos.y - sprite.getPosition().y <= TILESIZE * walklimit + TILESIZE) && (pos.y - sprite.getPosition().y >= 0) && ((pos.x - sprite.getPosition().x <= TILESIZE) && (pos.x - sprite.getPosition().x >= 0))) {		// omlaag
		b = true;
	}

	return b;
}

bool Unit::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}


void Unit::damage(int points) {
	hitpoints = hitpoints - points;
	if (hitpoints <= 0) {
		destroy();
	}
}


int Unit::attack() {
	return attackpoints;
}


void Unit::destroy() {
	// eerst maar ff alleen de kleur naar onzichtbaar
	sprite.setColor(sf::Color::Transparent);
}