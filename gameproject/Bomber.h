//File Bomber.h

#ifndef _BOMBER_H
#define _BOMBER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class Bomber : public Unit {
public:
	Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color);
	void action() override;											// dit is de actie die je unit uit kan voeren

private:
	int walklimit = 1;
	int hp = 100;
	int dp = 10;
};

#endif