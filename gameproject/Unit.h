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
	virtual void action();											// dit is de actie die je unit uit kan voeren
	void setSelected(bool sel);
	bool getSelected();


protected:
	textureID id;
	sf::Sprite sprite;
	sf::Color side;
	bool selected = false;
	int walklimit = 2;
};

#endif