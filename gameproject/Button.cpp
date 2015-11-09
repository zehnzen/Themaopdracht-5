//File Button.cpp

#include <SFML/Graphics.hpp>
#include "Button.h"

/**********************************************************************************************//**
 * @fn	Button::Button(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Button.
 * @param	textures	The textures of the Button.
 * @param	pos			The position of the Button on the screen.
 **************************************************************************************************/

Button::Button(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	numFrames = 1;
	repeat = true;
}

/**********************************************************************************************//**
 * @fn	bool Button::getClicked(sf::Vector2f pos)
 *
 * @brief	Gets a clicked.
 *
 * @param	pos	The position where is clicked on the screen.
 *
 * @return	true if Button is clicked, false if not.
 **************************************************************************************************/

bool Button::getClicked(sf::Vector2f pos) {
	return (sprite.getGlobalBounds().contains(pos)) ? true : false;
}

