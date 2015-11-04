//File Resource.cpp

#include "Resource.h"

/**********************************************************************************************//**
 * @fn	Resource::Resource(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 **************************************************************************************************/

Resource::Resource(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	repeat = true;

	setPosition(pos);
	numFrames = 1;
}

/**********************************************************************************************//**
 * @fn	int Resource::getResourceMoney()
 *
 * @brief	Gets resource money.
 *
 * @return	The resource money.
 **************************************************************************************************/

int Resource::getResourceMoney() {
	return resourceMoney;
}

/**********************************************************************************************//**
 * @fn	bool Resource::damage(int points)
 *
 * @brief	Damages.
 *
 * @param	points	The points.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool Resource::damage(int points) {
	hitpoints = hitpoints - points;
	if (hitpoints <= 0) {
		hitpoints = 0;
		return true;
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	bool Resource::checkClicked(sf::Vector2f pos)
 *
 * @brief	Check clicked.
 *
 * @param	pos	The position.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool Resource::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

/**********************************************************************************************//**
 * @fn	void Resource::setSelected(bool b)
 *
 * @brief	Sets a selected.
 *
 * @param	b	true to b.
 **************************************************************************************************/

void Resource::setSelected(bool b) {
	selected = b;
}

/**********************************************************************************************//**
 * @fn	void Resource::setOldSelected(bool b)
 *
 * @brief	Sets old selected.
 *
 * @param	b	true to b.
 **************************************************************************************************/

void Resource::setOldSelected(bool b) {
	oldSelected = b;
}

/**********************************************************************************************//**
 * @fn	bool Resource::getSelected()
 *
 * @brief	Gets the selected.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool Resource::getSelected() {
	return selected;
}

/**********************************************************************************************//**
 * @fn	bool Resource::makeSelected(sf::Vector2f pos)
 *
 * @brief	Makes a selected.
 *
 * @param	pos	The position.
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

bool Resource::makeSelected(sf::Vector2f pos) {
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

/**********************************************************************************************//**
 * @fn	int Resource::getMoney()
 *
 * @brief	Gets the money.
 *
 * @return	The money.
 **************************************************************************************************/

int Resource::getMoney() {
	int earned = 20;
	if (resourceMoney > 0) {
		earned = 100;
		resourceMoney -= earned;
	}
	if(resourceMoney <= 0) {
		sprite.setColor(sf::Color::Black);
	}
	return earned;
}