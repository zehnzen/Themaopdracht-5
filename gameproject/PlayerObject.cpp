//File PlayerObject.cpp

#include "PlayerObject.h"

/**********************************************************************************************//**
 * @fn	PlayerObject::PlayerObject(textureID id, const textureHolder & textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the PlayerObject.
 * @param	textures	The textures of the PlayerObject.
 * @param	pos			The position of the PlayerObject on the screen.
 * @param	color   	The color of the PlayerObject (tells which player owns this object, red/blue).
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
 * @brief	Gets the hitpoints.
 *
 * @return	The hitpoints.
 **************************************************************************************************/

int PlayerObject::getHP() {
	return hitpoints;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::damage(int points)
 *
 * @brief	Damages the PlayerObject.
 *
 * @param	points	The damage points.
 *
 * @return	true if PlayerObject ran out of hitpoints, false if not.
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
 * @brief	Check if the PlayerObject is being clicked on.
 *
 * @param	pos	The position of the mouse.
 *
 * @return	true if clicked on, false if not.
 **************************************************************************************************/

bool PlayerObject::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

/**********************************************************************************************//**
 * @fn	void PlayerObject::setSelected(bool b)
 *
 * @brief	Sets the PlayerObject to being selected.
 *
 * @param	b	true if selected, false if not.
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
 * @brief	Sets wheither or not the PlayerObject used to be selected.
 *
 * @param	b	true if selected, false if not.
 **************************************************************************************************/

void PlayerObject::setOldSelected(bool b) {
	oldSelected = b;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::getSelected()
 *
 * @brief	Gets wheither or not the PlayerObject is selected.
 *
 * @return	true if selected, false if not.
 **************************************************************************************************/

bool PlayerObject::getSelected() {
	return selected;
}

/**********************************************************************************************//**
 * @fn	bool PlayerObject::makeSelected(sf::Vector2f pos)
 *
 * @brief	Makes the PlayerObject selected or unselected.
 *
 * @param	pos	The position of the mouse.
 *
 * @return	true if selected, false if not.
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