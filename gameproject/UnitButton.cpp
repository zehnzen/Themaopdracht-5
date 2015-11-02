//File UnitButton.cpp

#include "UnitButton.h"

UnitButton::UnitButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	numFrames = 8;
}

Unit* UnitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) {
	std::cout << "Unit returned\n";
	return new Unit(textureID::UNIT, textures, pos, color, scale);
}

int UnitButton::getCostMoney() {
	return cost;
}

void UnitButton::handleMouse() {
	// hier wat hij moet doen
}
//---------------------------------------------------------------------------------------------------

DragonButton::DragonButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 500;
	numFrames = 5;
}

Unit* DragonButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) {
	std::cout << "Bomber returned\n";
	return new Bomber(textureID::DRAGON, textures, pos, color, scale);
}

//---------------------------------------------------------------------------------------------------
SoldierButton::SoldierButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	UnitButton{ id, textures, pos }
{
	cost = 200;
	numFrames = 6;
}

Unit* SoldierButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) {
	std::cout << "Soldier returned\n";
	return new Soldier(textureID::SOLDIER, textures, pos, color, scale);
}

