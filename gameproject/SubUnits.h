//File Bomber.h

#ifndef _BOMBER_H
#define _BOMBER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class Soldier : public Unit {
public:
	Soldier(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);
};

class Recruit : public Unit {
public:
	Recruit(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);
};

class Bomber : public Unit {
public:
	Bomber(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);
};

class Scout : public Unit {
public:
	Scout(textureID, const textureHolder& textuers, sf::Vector2f, sf::Color);
};

#endif