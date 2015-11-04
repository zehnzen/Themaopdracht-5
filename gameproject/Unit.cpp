//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"
#include "Terrain.h"

/**********************************************************************************************//**
 * @fn	Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Unit.
 * @param	textures	The textures of the Unit.
 * @param	pos			The position of the Unit in the screen.
 * @param	color   	The color of the Unit (blue/ red, depends on the active player).
 **************************************************************************************************/

Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	PlayerObject( id, textures, pos, color)
{
	setPosition(pos);

	resetTurn();

	if (color == sf::Color::Red) {
		sprite.setScale(-1.f, 1.f);
		sprite.setOrigin(50.f, 0.f);
	}

	unitName = "Unit";
}

/**********************************************************************************************//**
 * @fn	void Unit::setPosition(sf::Vector2f pos)
 *
 * @brief	Sets the position of the unit in the screen.
 *
 * @param	pos	The position of the unit.
 **************************************************************************************************/

void Unit::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos.x + SpriteOffset, pos.y + SpriteOffset);
}

/**********************************************************************************************//**
 * @fn	int Unit::getDP()
 *
 * @brief	Gets the attack points(damage points).
 *
 * @return	The attack points.
 **************************************************************************************************/

int Unit::getDP() {
	return attackpoints;
}

/**********************************************************************************************//**
 * @fn	int Unit::getWalklimit()
 *
 * @brief	Gets the walklimit of the unit.
 *
 * @return	The walklimit of the unit (how many tiles he can move).
 **************************************************************************************************/

int Unit::getWalklimit() {
	return turnWalklimit;
}

/**********************************************************************************************//**
 * @fn	std::string Unit::getName()
 *
 * @brief	Gets the name of the unit.
 *
 * @return	The name of the unit.
 **************************************************************************************************/

std::string Unit::getName() {
	return unitName;
}

/**********************************************************************************************//**
 * @fn	int Unit::getAttackrange()
 *
 * @brief	Gets the attackrange of the unit.
 *
 * @return	The attackrange of the unit (how many tiles his attack can reach).
 **************************************************************************************************/

int Unit::getAttackrange() {
	return turnAttackrange;
}

/**********************************************************************************************//**
 * @fn	void Unit::resetTurn()
 *
 * @brief	Resets the turn.
 **************************************************************************************************/

void Unit::resetTurn() {
	turnWalklimit = walklimit;
	turnAttackrange = attackrange;
}

/**********************************************************************************************//**
 * @fn	void Unit::walk(sf::Vector2f pos)
 *
 * @brief	Walks to the given position.
 *
 * @param	pos	The position where to walk to.
 **************************************************************************************************/

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

/**********************************************************************************************//**
 * @fn	int Unit::attack()
 *
 * @brief	Simulates an attack by setting the new attackrange to zero after the attack end returning the attack points.
 *
 * @return	the attack points.
 **************************************************************************************************/

int Unit::attack() {
	oldSelected = false;
	selected = false;
	sprite.setColor(side);
	turnAttackrange = 0;
	return attackpoints;
}

/**********************************************************************************************//**
 * @fn	void Unit::resource()
 *
 * @brief	Attackrange set to zero to simulate the resource being used.
 **************************************************************************************************/

void Unit::resource() {
	turnAttackrange = 0;
}
