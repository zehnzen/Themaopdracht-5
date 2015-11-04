//File Bomber.cpp

#include <SFML/Graphics.hpp>
#include "SubUnits.h"

/**********************************************************************************************//**
 * @fn	Soldier::Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 **************************************************************************************************/

Soldier::Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	hitpoints = 80;
	attackpoints = 30;
	walklimit = 3;
	attackrange = 4;
	resetTurn();

	unitName = "Soldier";
	numFrames = 6;
}

/**********************************************************************************************//**
 * @fn	Recruit::Recruit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 **************************************************************************************************/

Recruit::Recruit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	hitpoints = 100;
	attackpoints = 20;
	walklimit = 2;
	attackrange = 3;
	resetTurn();

	unitName = "Recruit";
	numFrames = 8;
}

/**********************************************************************************************//**
 * @fn	Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 **************************************************************************************************/

Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color}
{
	hitpoints = 150;
	attackpoints = 50;
	walklimit = 3;
	attackrange = 4;
	resetTurn();

	unitName = "Bomber";
	numFrames = 5;
}

/**********************************************************************************************//**
 * @fn	Scout::Scout(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 **************************************************************************************************/

Scout::Scout(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Unit{ id, textures, pos, color }
{
	hitpoints = 60;
	attackpoints = 20;
	walklimit = 4;
	attackrange = 4;
	resetTurn();

	unitName = "Scout";
	numFrames = 37;
	duration = sf::seconds(5);
}
