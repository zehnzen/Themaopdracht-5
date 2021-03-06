//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include "PlayerObject.h"
#include "string"

class Unit : public PlayerObject{
public:
	void setPosition(sf::Vector2f pos) override;

	void resetTurn();

	int getDP();
	int getWalklimit();
	std::string getName();

	int getAttackrange();

	void walk(sf::Vector2f pos);
	int attack();
	void resource();
	
protected:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	int walklimit = 2, attackrange = 3, turnWalklimit = walklimit, turnAttackrange = attackrange;
	int attackpoints = 20;
	std::string unitName;
};

#endif