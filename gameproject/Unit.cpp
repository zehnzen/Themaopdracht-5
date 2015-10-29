//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"
#include "Terrain.h"


Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	PlayerObject( id, textures, pos, color)
{
	setPosition(pos);

	walklimit = 2;
	attackrange = 3;

	numFrames = 1;
}

void Unit::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos.x + SpriteOffset, pos.y + SpriteOffset);
}

int Unit::getDP() {
	return attackpoints;
}

int Unit::getWalklimit() {
	return walklimit;
}


int Unit::getAttackrange() {
	return attackrange;
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


void Unit::walk(sf::Vector2f pos) {
	if (oldSelected) {
		setPosition(V2fModulo(pos, TILESIZE));
	}
	selected = false;
	oldSelected = false;
	sprite.setColor(side);
}

int Unit::attack() {
	oldSelected = false;
	selected = false;
	sprite.setColor(side);
	return attackpoints;
}

void Unit::action() {
}
