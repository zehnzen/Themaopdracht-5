//File Selectable.h

#ifndef _SELECTABLE_H
#define _SELECTABLE_H

#include "GameObject.h"

class Selectable : public GameObject {
public:
	void setSelected(bool);
	void setOldSelected(bool); //Kan eruit gehaald worden (misschien)

	bool getSelected();

	bool makeSelected(sf::Vector2f pos);
	bool checkClicked(sf::Vector2f pos);

protected:
	Selectable(textureID, const textureHolder& textures, sf::Vector2f);

	bool selected = false;
	bool oldSelected = false;
};

#endif