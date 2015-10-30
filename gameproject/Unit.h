//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include "PlayerObject.h"

class Unit : public PlayerObject{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	void setPosition(sf::Vector2f pos) override;

	void resetTurn();

	int getDP();
	int getWalklimit();

	int getAttackrange();

	void walk(sf::Vector2f pos);
	int attack();
	void resource();
	
protected:
	int walklimit = 2, attackrange = 3, turnWalklimit = walklimit, turnAttackrange = attackrange;
	int attackpoints = 20;
};

#endif