//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"
#include "Terrain.h"


Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	GameObject( id, textures, pos),
	side {color}
{
	sprite.setColor(color);
	setPos(pos);

	numFrames = 1;
	repeat = true;
}

void Unit::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos.x + SpriteOffset, pos.y + SpriteOffset);
}

int Unit::getHP() {
	return hitpoints;
}

int Unit::getDP() {
	return attackpoints;
}

int Unit::getWalklimit() {
	return walklimit;
}


bool Unit::makeSelected(sf::Vector2f pos) {
	setSelected(sprite.getGlobalBounds().contains(pos));
	if (selected) {
		if (oldSelected == false) {
			oldSelected = true;
		}
		else {
			selected = false;
			oldSelected = false;
		}
	}
	return selected;
}

void Unit::setSelected(bool b) {
	selected = b;
	if (selected) {
		sprite.setColor(sf::Color::Yellow);
	}
	else {
		sprite.setColor(side);
	}
}

void Unit::setOldSelected(bool b) {
	oldSelected = b;
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


void Unit::walk(sf::Vector2f pos, bool free) {
	if (checkWalk(pos) && oldSelected && free) {
		setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));
	}
	selected = false;
	oldSelected = false;
	sprite.setColor(side);
}

bool Unit::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

bool Unit::damage(int points) {
	hitpoints = hitpoints - points;
	if (hitpoints <= 0) {
		return true;
	}
	return false;
}

int Unit::attack() {
	oldSelected = false;
	selected = false;
	sprite.setColor(side);
	return attackpoints;
}

void Unit::action() {

}

bool Unit::makeSelected(sf::Vector2f pos) {
	setSelected(sprite.getGlobalBounds().contains(pos));
	if (selected) {
		if (oldSelected == false) {
			oldSelected = true;
		}
		else {
			selected = false;
			oldSelected = false;
		}
	}
	return selected;
}
