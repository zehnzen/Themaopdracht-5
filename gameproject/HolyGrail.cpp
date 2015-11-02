//File HolyGrail.cpp

#include "HolyGrail.h"

HolyGrail::HolyGrail(textureID id, const textureHolder & textures, sf::Vector2f pos):
	GameObject{ id, textures, pos }
{}

void HolyGrail::Reckoning(CommandQueue & queue, sf::Color color) {
	Command command;
	command.id = ((color == sf::Color::Blue) ? commandID::DMGRED : commandID::DMGBLUE);
	queue.push(command);
}