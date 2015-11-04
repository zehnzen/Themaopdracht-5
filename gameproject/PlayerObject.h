//File PlayerObject.h

#ifndef _PLAYEROBJECT_H
#define _PLAYEROBJECT_H

#include "GameObject.h"

class PlayerObject : public GameObject {
public:
	void setSelected(bool);
	void setOldSelected(bool); //Kan eruit gehaald worden (misschien)

	bool getSelected();
	int getHP();

	bool makeSelected(sf::Vector2f pos);
	bool checkClicked(sf::Vector2f pos);

	bool damage(int points);

protected:
	PlayerObject(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	sf::Color side;

	bool selected = false;
	bool oldSelected = false;// naar kijken

	int hitpoints = 100;
};

#endif