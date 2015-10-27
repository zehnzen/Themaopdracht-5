//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include "GameObject.h"

class Unit : public GameObject{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	void setPos(sf::Vector2f pos) override;
	void setSelected(bool);
	
	bool getSelected();
	int getWalklimit();
	int getHP();
	int getDP();

	void handleMouse(sf::Vector2f pos) override;

	virtual void action();											// dit is de actie die je unit uit kan voeren
	
protected:
	sf::Color side;
	bool selected = false;
	int walklimit = 2;
	int hp = 100;
	int dp = 50;
};

#endif