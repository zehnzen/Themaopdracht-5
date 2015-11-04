//File PlayerButton.cpp

#include "PlayerButton.h"

/**********************************************************************************************//**
 * @fn	PlayerButton::PlayerButton(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 **************************************************************************************************/

PlayerButton::PlayerButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button( id, textures, pos )
{}

/**********************************************************************************************//**
 * @fn	void PlayerButton::handleClick(CommandQueue & queue)
 *
 * @brief	Handles the click described by queue.
 *
 * @param [in,out]	queue	The queue.
 **************************************************************************************************/

void PlayerButton::handleClick(CommandQueue & queue) {
}

/**********************************************************************************************//**
 * @fn	EndTurnButton::EndTurnButton(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 **************************************************************************************************/

EndTurnButton::EndTurnButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton( id, textures, pos )
{}

/**********************************************************************************************//**
 * @fn	void EndTurnButton::handleClick(CommandQueue & queue)
 *
 * @brief	Handles the click described by queue.
 *
 * @param [in,out]	queue	The queue.
 **************************************************************************************************/

void EndTurnButton::handleClick(CommandQueue & queue) {
	Command command;
	command.id = commandID::SWITCHPLAYER;
	queue.push(command);
}

/**********************************************************************************************//**
 * @fn	WonButton::WonButton(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier.
 * @param	textures	The textures.
 * @param	pos			The position.
 **************************************************************************************************/

WonButton::WonButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton( id, textures, pos )
{}

/**********************************************************************************************//**
 * @fn	void WonButton::handleClick(CommandQueue & queue)
 *
 * @brief	Handles the click described by queue.
 *
 * @param [in,out]	queue	The queue.
 **************************************************************************************************/

void WonButton::handleClick(CommandQueue & queue) {
	Command command;
	command.id = commandID::NEWGAME;
	queue.push(command);
}

