//File Resource.h

#ifndef _RESOURCE_H
#define _RESOURCE_H

#include "Building.h"

class Resource : public GameObject {
public:
	Resource(textureID, const textureHolder& textures, sf::Vector2f);

	void setSelected(bool);
	void setOldSelected(bool);

	bool getSelected();
	int getResourceMoney();

	bool makeSelected(sf::Vector2f pos);
	bool checkClicked(sf::Vector2f pos);

	int getMoney();			// geeft geld terug zolang de resource nog niet uitgeput is

protected:
	bool selected = false;
	bool oldSelected = false;

	int resourceMoney = 800;
};

#endif