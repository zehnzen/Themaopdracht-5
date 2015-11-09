//File Building.cpp

#include "Building.h"

/**********************************************************************************************//**
 * @fn	Building::Building(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Building.
 * @param	textures	The textures of the Building.
 * @param	pos			The position of the Building on the field.
 * @param	color   	The color of the Building, tells which player is the owner of it.
 **************************************************************************************************/

Building::Building(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	PlayerObject{ id, textures, pos, color }
{
	numFrames = 1;
}

/**********************************************************************************************//**
 * @fn	void Building::checkAction(CommandQueue & queue)
 *
 * @brief	Check action.
 *
 * @param [in,out]	queue	The commandqueue which contains all the commands.
 **************************************************************************************************/

void Building::checkAction(CommandQueue & queue) {}

/**********************************************************************************************//**
 * @fn	Headquarters::Headquarters(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the HQ.
 * @param	textures	The textures for the HQ.
 * @param	pos			The position of the HQ on the field.
 * @param	color   	The color of the HQ, tells which player is the owner of it.
 **************************************************************************************************/

Headquarters::Headquarters(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color):
	Building( id, textures, pos, color )
{}

/**********************************************************************************************//**
 * @fn	void Headquarters::checkAction(CommandQueue & queue)
 *
 * @brief	Check action.
 *
 * @param [in,out]	queue	The commandqueue which contains all the commands.
 **************************************************************************************************/

void Headquarters::checkAction(CommandQueue & queue) {
	if (hitpoints <= 0) {
		Command command;
		command.id = commandID::WON;
		queue.push(command);
	}
}

/**********************************************************************************************//**
 * @fn	Factory::Factory(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Factory.
 * @param	textures	The textures of the Factory.
 * @param	pos			The position of the Factory on the field.
 * @param	color   	The color of the Factory, tells which player is the owner of it.
 **************************************************************************************************/

Factory::Factory(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Building( id, textures, pos, color )
{}

/**********************************************************************************************//**
 * @fn	void Factory::checkAction(CommandQueue & queue)
 *
 * @brief	Check action.
 *
 * @param [in,out]	queue	The commandqueue which contains all the commands.
 **************************************************************************************************/

void Factory::checkAction(CommandQueue & queue) {
	if (!(hitpoints <= 0)) {
		Command command;
		command.id = commandID::OPENFACTORY;
		queue.push(command);
	}
}

