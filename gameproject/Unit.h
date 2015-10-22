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
	void handleMouse(sf::Vector2f pos);
	void setSelected(bool sel);
	bool getSelected();

	bool checkWalk(sf::Vector2f pos);
	bool checkClicked(sf::Vector2f pos);


	void damage(int points);
	int attack();
	void destroy();	// vernietigen als geen hp meer


protected:
	textureID id;
	sf::Sprite sprite;
	sf::Color side;
	bool selected = false;
	int walklimit = 2;

	int hitpoints = 100;		// hp
	int attackpoints = 20;
};

#endif