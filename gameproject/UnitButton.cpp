//File UnitButton.cpp

#include "UnitButton.h"

UnitButton::UnitButton(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
}

Unit* UnitButton::bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) {
	std::cout << "Unit returnd\n";
	return new Unit(textureID::UNIT, textures, pos, color);
}

int UnitButton::getCostMoney() {
	return cost;
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

