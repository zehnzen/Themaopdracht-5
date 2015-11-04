//File Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"

/**********************************************************************************************//**
 * @fn	Player::Player(sf::Color side, bool set)
 *
 * @brief	Constructor.
 *
 * @param	side	The color of the player (which side he is on).
 * @param	set 	true if active, false if not.
 **************************************************************************************************/

Player::Player(sf::Color side, bool set):
	side {side},
	active{set}
{}

/**********************************************************************************************//**
 * @fn	sf::Color Player::getPlayer()
 *
 * @brief	Gets the color of the player.
 *
 * @return	The color of the player (color is like an id tag for the player).
 **************************************************************************************************/

sf::Color Player::getPlayer() {
	return side;
}

/**********************************************************************************************//**
 * @fn	bool Player::getActive()
 *
 * @brief	Gets wheiter or not the player is active.
 *
 * @return	true if active, false if not.
 **************************************************************************************************/

bool Player::getActive() {
	return active;
}

/**********************************************************************************************//**
 * @fn	void Player::setActive(bool set)
 *
 * @brief	Sets the activity of the player.
 *
 * @param	set	true if active, false if not.
 **************************************************************************************************/

void Player::setActive(bool set) {
	active = set;
}

/**********************************************************************************************//**
 * @fn	int Player::getPoints()
 *
 * @brief	Gets the points of the player.
 *
 * @return	The points of the player.
 **************************************************************************************************/

int	Player::getPoints() {
	return points;
}

/**********************************************************************************************//**
 * @fn	void Player::substractPoints(CommandQueue & queue)
 *
 * @brief	Substract points.
 *
 * @param [in,out]	queue	The queue.
 **************************************************************************************************/

void Player::substractPoints(CommandQueue & queue) {
	points -= 10; //Momenteel de standaard value die per unit rond de resource van de vijand wordt afgetrokken.
	if (points <= 0) {
		Command command;
		command.id = commandID::WON;
		queue.push(command);
	}
}

/**********************************************************************************************//**
 * @fn	int Player::getMoney()
 *
 * @brief	Gets the money of the player.
 *
 * @return	The money of the player.
 **************************************************************************************************/

int Player::getMoney() {
	return money;
}

/**********************************************************************************************//**
 * @fn	void Player::setMoney(int mon)
 *
 * @brief	Sets the money value of the player.
 *
 * @param	mon	The money.
 **************************************************************************************************/

void Player::setMoney(int mon) {
	money = mon;
}

/**********************************************************************************************//**
 * @fn	void Player::setUnitSelected(bool usel)
 *
 * @brief	Sets wheither a unit is selected or not.
 *
 * @param	usel	true if unit is selected, false if not.
 **************************************************************************************************/

void Player::setUnitSelected(bool usel) {
	unitSelected = usel;
}

/**********************************************************************************************//**
 * @fn	bool Player::getUnitSelected()
 *
 * @brief	Gets if a unit is selected.
 *
 * @return	true if unit is selected, false if not.
 **************************************************************************************************/

bool Player::getUnitSelected() {
	return unitSelected;
}

/**********************************************************************************************//**
 * @fn	int Player::getUnitAttacks()
 *
 * @brief	Gets the number unit attacks left.
 *
 * @return	The unit attacks left for this turn.
 **************************************************************************************************/

int Player::getUnitAttacks() {
	return unitAttacks;
}

/**********************************************************************************************//**
 * @fn	void Player::setUnitAttacks(int attacks)
 *
 * @brief	Sets the number unit attacks for this turn.
 *
 * @param	attacks	The number of unit attacks for this turn.
 **************************************************************************************************/

void Player::setUnitAttacks(int attacks) {
	unitAttacks = attacks;
}

/**********************************************************************************************//**
 * @fn	void Player::diffUnitAttacks(int attacks)
 *
 * @brief	Difference the number of unit attacks.
 *
 * @param	attacks	The number of unit attacks for this turn.
 **************************************************************************************************/

void Player::diffUnitAttacks(int attacks) {
	unitAttacks += attacks;
}

/**********************************************************************************************//**
 * @fn	int Player::getUnitWalks()
 *
 * @brief	Gets the number of units that can still walk this turn.
 *
 * @return	The number of units that can still walk this turn.
 **************************************************************************************************/

int Player::getUnitWalks() {
	return unitWalks;
}

/**********************************************************************************************//**
 * @fn	void Player::resetUnitWalks()
 *
 * @brief	Resets the number of units that can walk this turn.
 **************************************************************************************************/

void Player::resetUnitWalks() {
	unitWalks = 0;
}

/**********************************************************************************************//**
 * @fn	void Player::diffUnitWalks(int steps)
 *
 * @brief	Difference the number of units that can walk this turn.
 *
 * @param	steps	The number of units already walked this turn.
 **************************************************************************************************/

void Player::diffUnitWalks(int steps) {
	unitWalks += steps;
}