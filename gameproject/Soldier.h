//File Soldier.h

#ifndef _SOLDIER_H
#define _SOLDIER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class Soldier : public Unit {
public:
	Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color, int scale);
};

#endif