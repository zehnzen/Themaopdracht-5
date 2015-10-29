//File Terrain.h

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Enums.h"
#include "GameObject.h"

class Terrain : public GameObject{
public:
	Terrain(textureID, const textureHolder& textures, sf::Vector2f);

	void changeColor(sf::Color col);

	sf::Color getColor();
	bool checkClicked(sf::Vector2f pos);

	bool getFree();
	void setFree(bool f);

private:
	bool free = true;
};

#endif