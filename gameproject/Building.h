//File Building.h

#ifndef _BUILDING_H
#define _BUILDING_H

#include "PlayerObject.h"
#include "CommandQueue.h"

class Building : public PlayerObject {
public:
	Building(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	virtual void checkAction(CommandQueue & command);
};

class Headquarters : public Building {
public:
	Headquarters(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	void checkAction(CommandQueue & command) override;
};

class Factory : public Building {
public:
	Factory(textureID, const textureHolder& textures, sf::Vector2f, sf::Color);

	void checkAction(CommandQueue & command) override;
};

#endif