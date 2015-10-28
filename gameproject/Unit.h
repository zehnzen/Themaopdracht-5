//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include "GameObject.h"

class Unit : public GameObject{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	void setPos(sf::Vector2f pos) override;
	void setSelected(bool);
	void setOldSelected(bool);

	bool getSelected();
	int getHP();
	int getDP();
	int getWalklimit();
	int getAttackrange();
	bool makeSelected(sf::Vector2f pos);

	bool checkWalk(sf::Vector2f pos);
	bool checkClicked(sf::Vector2f pos);

	void walk(sf::Vector2f pos);
	bool damage(int points);
	int attack();

	virtual void action();											// dit is de actie die je unit uit kan voeren
	
protected:
	sf::Color side;
	bool selected = false;
	bool oldSelected = false;
	int walklimit = 2;
	int attackrange = 3;

	int hitpoints = 100;
	int attackpoints = 20;
};

#endif