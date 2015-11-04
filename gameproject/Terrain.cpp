//File Terrain.cpp

#include <SFML/Graphics.hpp>
#include "Terrain.h"

/**********************************************************************************************//**
 * @fn	Terrain::Terrain(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Terrain.
 * @param	textures	The textures of the Terrain.
 * @param	pos			The position of the Terrain on the screen.
 **************************************************************************************************/

Terrain::Terrain(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	sprite.setColor(sf::Color::White);
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
}

/**********************************************************************************************//**
 * @fn	void Terrain::changeColor(sf::Color col)
 *
 * @brief	Change the color of the terrain tile.
 *
 * @param	col	The color of the terrain.
 **************************************************************************************************/

void Terrain::changeColor(sf::Color col) {
	sprite.setColor(col);
}

/**********************************************************************************************//**
 * @fn	sf::Color Terrain::getColor()
 *
 * @brief	Gets the color of the terrain.
 *
 * @return	The color of the terrain.
 **************************************************************************************************/

sf::Color Terrain::getColor() {
	sf::Color color = sprite.getColor();
	return color;
}

/**********************************************************************************************//**
 * @fn	bool Terrain::checkClicked(sf::Vector2f pos)
 *
 * @brief	Check wheither or not a terrain tile is being clicked on.
 *
 * @param	pos	The position of the mouse.
 *
 * @return	true if clicked on, false if not.
 **************************************************************************************************/

bool Terrain::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

/**********************************************************************************************//**
 * @fn	bool Terrain::getFree()
 *
 * @brief	Gets wheither or not the terrain tile is free (has nothing on it).
 *
 * @return	true if free, false if not.
 **************************************************************************************************/

bool Terrain::getFree() {
	return free;
}

/**********************************************************************************************//**
 * @fn	void Terrain::setFree(bool f)
 *
 * @brief	Sets the terrain tile free.
 *
 * @param	f	true if free, false if not.
 **************************************************************************************************/

void Terrain::setFree(bool f) {
	free = f;
}