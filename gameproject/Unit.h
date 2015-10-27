//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"

class Unit{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);
	void setTexture(sf::Texture & text);
	void setPos(sf::Vector2f pos);
	sf::Vector2f getPosition();
	int getWalklimit();
	void draw(sf::RenderWindow & window);
	bool makeSelected(sf::Vector2f pos);				// ff andere manier proberen dan via handleMouse
	void setSelected(bool sel);
	void setOldSelected(bool osel);
	bool getSelected();

	bool checkWalk(sf::Vector2f pos);
	void Unit::walk(sf::Vector2f pos, bool free);		// free betekent dat de plek waar hij wil lopen vrij toegankelijk is (niet bezit door iets anders)
	bool checkClicked(sf::Vector2f pos);


	bool damage(int points);
	int attack();


protected:
	textureID id;
	sf::Sprite sprite;
	sf::Color side;
	bool selected = false;
	bool oldSelected = false;
	int walklimit = 2;

	int hitpoints = 100;		// hp
	int attackpoints = 20;
};

#endif