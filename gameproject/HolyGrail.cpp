//File HolyGrail.cpp

#include "HolyGrail.h"

/**********************************************************************************************//**
 * @fn	HolyGrail::HolyGrail(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the Holy Grail.
 * @param	textures	The textures of the Holy Grail.
 * @param	pos			The position of the Holy Grail on the screen.
 **************************************************************************************************/

HolyGrail::HolyGrail(textureID id, const textureHolder & textures, sf::Vector2f pos):
	GameObject{ id, textures, pos }
{}

/**********************************************************************************************//**
 * @fn	void HolyGrail::Reckoning(CommandQueue & queue, sf::Color color)
 *
 * @brief	Deals damage to the other team if units of a team are nearby.
 *
 * @param [in,out]	queue	The queue.
 * @param	color		 	The color of the team that's nearby.
 **************************************************************************************************/

void HolyGrail::Reckoning(CommandQueue & queue, sf::Color color) {
	Command command;
	command.id = ((color == sf::Color::Blue) ? commandID::DMGRED : commandID::DMGBLUE);
	queue.push(command);
}