//File Terrain.h

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Enums.h"

class Terrain {
public:
	Terrain(textureID, const textureHolder& textures);
	Terrain(textureID, const textureHolder& textures, sf::Vector2f);
	void setPosition(sf::Vector2f);
	void draw(sf::RenderWindow & window);
	void changeColor(sf::Color col);
	
private:
	textureID id;
	sf::Sprite sprite;
};

#endif