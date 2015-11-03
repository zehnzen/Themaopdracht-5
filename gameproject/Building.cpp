//File Building.cpp

#include "Building.h"

Building::Building(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	PlayerObject(id, textures, pos, color)
{
	numFrames = 1;
}

void Building::checkAction(CommandQueue & queue) {}

Headquarters::Headquarters(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color):
	Building( id, textures, pos, color )
{}

void Headquarters::checkAction(CommandQueue & queue) {
	if (hitpoints <= 0) {
		Command command;
		command.id = commandID::WON;
		queue.push(command);
	}
}

Factory::Factory(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Building( id, textures, pos, color )
{}

void Factory::checkAction(CommandQueue & queue) {
	if (!(hitpoints <= 0)) {
		Command command;
		command.id = commandID::OPENFACTORY;
		queue.push(command);
	}
}

