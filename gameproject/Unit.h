//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include "PlayerObject.h"

class Unit : public PlayerObject{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	void setPosition(sf::Vector2f pos) override;

	int getDP();
	int getWalklimit();

	int getAttackrange();

	bool checkWalk(sf::Vector2f pos);

	void walk(sf::Vector2f pos);
	int attack();

	virtual void action();											// dit is de actie die je unit uit kan voeren
	
protected:
	int walklimit = 2;
	int attackrange = 3;
	int attackpoints = 20;
};

#endif