//File Bomber.cpp

#include <SFML/Graphics.hpp>
#include "SubUnits.h"

/**********************************************************************************************//**
 * @fn	Soldier::Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Soldier.
 * @param	textures	The textures of the Soldier.
 * @param	pos			The position of the Soldier on the screen.
 * @param	color   	The color of the Soldier (tells which player is the owner).
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
 * @param	id			The identifier of the Recruit.
 * @param	textures	The textures of the Recruit.
 * @param	pos			The position of the Recruit on the screen.
 * @param	color   	The color of the Recruit (tells which player is the owner).
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
	numFrames = 5;
}

/**********************************************************************************************//**
 * @fn	Bomber::Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Bomber.
 * @param	textures	The textures of the Bomber.
 * @param	pos			The position of the Bomber on the screen.
 * @param	color   	The color of the Bomber (tells which player is the owner).
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
 * @param	id			The identifier of the Scout.
 * @param	textures	The textures of the Scout.
 * @param	pos			The position of the Scout on the screen.
 * @param	color   	The color of the Scout (tells which player is the owner).
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
	numFrames = 5;
}
