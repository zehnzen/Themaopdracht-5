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
	resetTurn();

	numFrames = 1;
}

void Unit::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos.x + SpriteOffset, pos.y + SpriteOffset);
}

int Unit::getDP() {
	return attackpoints;
}

int Unit::getWalklimit() {
	return turnWalklimit;
}

std::string Unit::getName() {
	return unitName;
}


int Unit::getAttackrange() {
	return turnAttackrange;
}

void Unit::resetTurn() {
	turnWalklimit = walklimit;
	turnAttackrange = attackrange;
}

void Unit::walk(sf::Vector2f pos) {
	sf::Vector2f newPos = V2fModulo(pos, TILESIZE);
	sf::Vector2f previous = getTilePosition();

	setPosition(newPos);

	selected = false;
	oldSelected = false;
	sprite.setColor(side);

	int walkDeducted = 0;
	while (previous.x > newPos.x) {
		previous.x -= TILESIZE;
		walkDeducted++;
	}
	while (previous.x < newPos.x) {
		previous.x += TILESIZE;
		walkDeducted++;
	}
	while (previous.y > newPos.y) {
		previous.y -= TILESIZE;
		walkDeducted++;
	}
	while (previous.y < newPos.y) {
		previous.y += TILESIZE;
		walkDeducted++;
	}
	turnWalklimit -= walkDeducted;	
}

int Unit::attack() {
	oldSelected = false;
	selected = false;
	sprite.setColor(side);
	turnAttackrange = 0;
	return attackpoints;
}

void Unit::resource() {
	turnAttackrange = 0;
}
