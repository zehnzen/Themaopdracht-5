//File Building.h

#ifndef _BUILDING_H
#define _BUILDING_H

#include "PlayerObject.h"

class Building : public PlayerObject {
public:
	Building(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);
};

#endif