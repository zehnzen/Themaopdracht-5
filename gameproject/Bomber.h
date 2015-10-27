//File Bomber.h

#ifndef _BOMBER_H
#define _BOMBER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class Bomber : public Unit {
public:
	Bomber(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color);
	void action() override;											// dit is de actie die je unit uit kan voeren
	void update(sf::Time);
	int getHP();
	int getDP();
	int getWalklimit();

private:
	int walklimit = 3;
	int hp = 150;
	int dp = 50;
};

#endif