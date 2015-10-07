//File Soldier.h

#ifndef _SOLDIER_H
#define _SOLDIER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class Soldier : public Unit {
public:
	Soldier(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color);
	void action() override;											// dit is de actie die je unit uit kan voeren
	int getHP();
	int getDP();
	int getWalklimit();

private:
	int walklimit = 1;
	int hp = 100;
	int dp = 10;
};

#endif