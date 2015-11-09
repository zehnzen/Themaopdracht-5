//File UnitButton.cpp

#include "UnitButton.h"

/**********************************************************************************************//**
 * @fn	UnitButton::UnitButton(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the UnitButton.
 * @param	textures	The textures of the UnitButton.
 * @param	pos			The position of the UnitButton on the screen.
 **************************************************************************************************/

UnitButton::UnitButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	
}

/**********************************************************************************************//**
 * @fn	Unit* UnitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Actions.
 *
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 *
 * @return	null if it fails, else an Unit*.
 **************************************************************************************************/

Unit* UnitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "WRONG UNITBUTTON";
	return new Recruit(textureID::RECRUIT, textures, pos, color);
}

/**********************************************************************************************//**
 * @fn	int UnitButton::getCostMoney()
 *
 * @brief	Gets how much money the unit costs.
 *
 * @return	The amount of money the unit costs.
 **************************************************************************************************/

int UnitButton::getCostMoney() {
	return cost;
}

/**********************************************************************************************//**
 * @fn	RecruitButton::RecruitButton(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the RecruitButton.
 * @param	textures	The textures of the RecruitButton.
 * @param	pos			The position of the RecruitButton on the screen.
 **************************************************************************************************/

RecruitButton::RecruitButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	numFrames = 5;
}

/**********************************************************************************************//**
 * @fn	Unit* RecruitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Actions.
 *
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 *
 * @return	null if it fails, else an Unit*.
 **************************************************************************************************/

Unit* RecruitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Unit returned\n";
	return new Recruit(textureID::RECRUIT, textures, pos, color);
}

/**********************************************************************************************//**
 * @fn	DragonButton::DragonButton(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the DragonButton.
 * @param	textures	The textures of the DragonButton.
 * @param	pos			The position of the DragonButton on the screen.
 **************************************************************************************************/

DragonButton::DragonButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 500;
	numFrames = 5;
}

/**********************************************************************************************//**
 * @fn	Unit* DragonButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Actions.
 *
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 *
 * @return	null if it fails, else an Unit*.
 **************************************************************************************************/

Unit* DragonButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Bomber returned\n";
	return new Bomber(textureID::DRAGON, textures, pos, color);
}

//---------------------------------------------------------------------------------------------------

/**********************************************************************************************//**
 * @fn	SoldierButton::SoldierButton(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the SoldierButton.
 * @param	textures	The textures of the SoldierButton.
 * @param	pos			The position of the SoldierButton on the screen.
 **************************************************************************************************/

SoldierButton::SoldierButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 200;
	numFrames = 6;
}

/**********************************************************************************************//**
 * @fn	Unit* SoldierButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Actions.
 *
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 *
 * @return	null if it fails, else an Unit*.
 **************************************************************************************************/

Unit* SoldierButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Soldier returned\n";
	return new Soldier(textureID::SOLDIER, textures, pos, color);
}

/**********************************************************************************************//**
 * @fn	ScoutButton::ScoutButton(textureID id, const textureHolder & textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the ScoutButton.
 * @param	textures	The textures of the ScoutButton.
 * @param	pos			The position of the ScoutButton on the screen.
 **************************************************************************************************/

ScoutButton::ScoutButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 200;
	numFrames = 5;
	//duration = sf::seconds(4);
	//NUMFRAMES OPZOEKEN
}

/**********************************************************************************************//**
 * @fn	Unit* ScoutButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color)
 *
 * @brief	Actions.
 *
 * @param	textures	The textures.
 * @param	pos			The position.
 * @param	color   	The color.
 *
 * @return	null if it fails, else an Unit*.
 **************************************************************************************************/

Unit* ScoutButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Scout returned\n";
	return new Scout(textureID::SCOUT, textures, pos, color);
}


