//File PlayerObject.cpp

#include "PlayerObject.h"

/**********************************************************************************************//**
 * @fn	PlayerObject::PlayerObject(textureID id, const textureHolder & textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 **************************************************************************************************/

PlayerObject::PlayerObject(textureID id, const textureHolder & textures, sf::Vector2f pos, sf::Color color):
	GameObject(id, textures, pos),
	side{ color }
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	sprite.setColor(color);
	repeat = true;
}

/**********************************************************************************************//**
 * @fn	int PlayerObject::getHP()
 *
 * @brief	Gets the hp.
 *
 * @return	The hp.
 **************************************************************************************************/

int PlayerObject::getHP() {
	return hitpoints;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::damage(int points)
 *
 * @brief	Damages.
 *
 * @param	points	The points.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool PlayerObject::damage(int points) {
	hitpoints = hitpoints - points;
	if (hitpoints <= 0) {
		hitpoints = 0;
		return true;
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::checkClicked(sf::Vector2f pos)
 *
 * @brief	Check clicked.
 *
 * @param	pos	The position.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool PlayerObject::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

/**********************************************************************************************//**
 * @fn	void PlayerObject::setSelected(bool b)
 *
 * @brief	Sets a selected.
 *
 * @param	b	true to b.
 **************************************************************************************************/

void PlayerObject::setSelected(bool b) {
	selected = b;
	if (selected) {
		sprite.setColor(sf::Color::Yellow);
	}
	else {
		sprite.setColor(side);
	}
}

/**********************************************************************************************//**
 * @fn	void PlayerObject::setOldSelected(bool b)
 *
 * @brief	Sets old selected.
 *
 * @param	b	true to b.
 **************************************************************************************************/

void PlayerObject::setOldSelected(bool b) {
	oldSelected = b;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::getSelected()
 *
 * @brief	Gets the selected.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool PlayerObject::getSelected() {
	return selected;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::makeSelected(sf::Vector2f pos)
 *
 * @brief	Makes a selected.
 *
 * @param	pos	The position.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool PlayerObject::makeSelected(sf::Vector2f pos) {
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