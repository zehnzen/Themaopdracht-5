//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include "Entity.h"

class Unit : public Entity{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);
	void setPos(sf::Vector2f pos) override;
	sf::Vector2f getTilePosition();
	virtual int getWalklimit();

	void handleMouse(sf::Vector2f pos) override;
	void update(sf::Time) override;

	virtual void action();											// dit is de actie die je unit uit kan voeren
	void setSelected(bool sel);
	bool getSelected();


protected:
	sf::Color side;
	bool selected = false;
	int walklimit = 2;
};

#endif