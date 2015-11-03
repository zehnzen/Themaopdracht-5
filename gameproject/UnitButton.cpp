//File UnitButton.cpp

#include "UnitButton.h"

UnitButton::UnitButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	
}

Unit* UnitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "WRONG UNITBUTTON";
	return new Recruit(textureID::RECRUIT, textures, pos, color);
}

int UnitButton::getCostMoney() {
	return cost;
}

void UnitButton::handleMouse() {
	// hier wat hij moet doen
}
//---------------------------------------------------------------------------------------------------

RecruitButton::RecruitButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	numFrames = 8;
}

Unit* RecruitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Unit returned\n";
	return new Recruit(textureID::RECRUIT, textures, pos, color);
}


DragonButton::DragonButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 500;
	numFrames = 5;
}

Unit* DragonButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Bomber returned\n";
	return new Bomber(textureID::DRAGON, textures, pos, color);
}

//---------------------------------------------------------------------------------------------------
SoldierButton::SoldierButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 200;
	numFrames = 6;
}

Unit* SoldierButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Soldier returned\n";
	return new Soldier(textureID::SOLDIER, textures, pos, color);
}

ScoutButton::ScoutButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 200;
	numFrames = 37;
	duration = sf::seconds(5);
	//NUMFRAMES OPZOEKEN
}

Unit* ScoutButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Scout returned\n";
	return new Scout(textureID::SCOUT, textures, pos, color);
}


