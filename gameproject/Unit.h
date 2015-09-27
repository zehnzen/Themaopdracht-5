//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"

class Unit{
public:
	Unit(textureID, const textureHolder& textures, sf::Vector2f);
	void setTexture(sf::Texture & text);
	void setPos(sf::Vector2f pos);
	void draw(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window, sf::Vector2f position);	// draw methode met position erbij
	void handleMouse(sf::Vector2f pos);
	void action();											// dit is de actie die je unit uit kan voeren


private:
	textureID id;
	sf::Sprite sprite;
	bool selected = false;
};

#endif