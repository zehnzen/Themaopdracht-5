//File Resource.cpp

#include "Resource.h"

/**********************************************************************************************//**
 * @fn	Resource::Resource(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Resource.
 * @param	textures	The textures of the Resource.
 * @param	pos			The position of the Resource on the screen.
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
 * @brief	Gets the money left in the resource.
 *
 * @return	The money left in the resource.
 **************************************************************************************************/

int Resource::getResourceMoney() {
	return resourceMoney;
}

/**********************************************************************************************//**
 * @fn	bool Resource::checkClicked(sf::Vector2f pos)
 *
 * @brief	Check wheiter or not the resource is clicked on.
 *
 * @param	pos	The position of the mouse.
 *
 * @return	true if clicked on, false if not.
 **************************************************************************************************/

bool Resource::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

/**********************************************************************************************//**
 * @fn	void Resource::setSelected(bool b)
 *
 * @brief	Sets the resource to being selected or unselected.
 *
 * @param	b	true if selected, false if not.
 **************************************************************************************************/

void Resource::setSelected(bool b) {
	selected = b;
}

/**********************************************************************************************//**
 * @fn	void Resource::setOldSelected(bool b)
 *
 * @brief	Sets if the resource used to be selected or not.
 *
 * @param	b	true if selected, false if not.
 **************************************************************************************************/

void Resource::setOldSelected(bool b) {
	oldSelected = b;
}

/**********************************************************************************************//**
 * @fn	bool Resource::getSelected()
 *
 * @brief	Gets wheiter or not the resource is selected.
 *
 * @return	true if selected, false if not.
 **************************************************************************************************/

bool Resource::getSelected() {
	return selected;
}

/**********************************************************************************************//**
 * @fn	bool Resource::makeSelected(sf::Vector2f pos)
 *
 * @brief	Makes the resource selected or unselected (depends on the mouseposition).
 *
 * @param	pos	The position of the mouse.
 *
 * @return	true if selected, false if not.
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
 * @brief	Gets money from the resource.
 *
 * @return	The money gotton from the resource.
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