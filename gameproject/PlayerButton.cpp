//File PlayerButton.cpp

#include "PlayerButton.h"

/**********************************************************************************************//**
 * @fn	PlayerButton::PlayerButton(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the PlayerButton.
 * @param	textures	The textures of the PlayerButton.
 * @param	pos			The position of the PlayerButton on the screen.
 **************************************************************************************************/

PlayerButton::PlayerButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button( id, textures, pos )
{}

/**********************************************************************************************//**
 * @fn	void PlayerButton::handleClick(CommandQueue & queue)
 *
 * @brief	Handles mouse clicks.
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
 * @param	id			The identifier of the EndTurnButton.
 * @param	textures	The textures of the EndTurnButton.
 * @param	pos			The position of the EndTurnButton on the screen.
 **************************************************************************************************/

EndTurnButton::EndTurnButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton( id, textures, pos )
{}

/**********************************************************************************************//**
 * @fn	void EndTurnButton::handleClick(CommandQueue & queue)
 *
 * @brief	Handles the mouse click.
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
 * @param	id			The identifier of the WonButton.
 * @param	textures	The textures of the WonButton.
 * @param	pos			The position of the WonButton on the screen.
 **************************************************************************************************/

WonButton::WonButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton( id, textures, pos )
{}

/**********************************************************************************************//**
 * @fn	void WonButton::handleClick(CommandQueue & queue)
 *
 * @brief	Handles the mouse click.
 *
 * @param [in,out]	queue	The queue.
 **************************************************************************************************/

void WonButton::handleClick(CommandQueue & queue) {
	Command command;
	command.id = commandID::NEWGAME;
	queue.push(command);
}

