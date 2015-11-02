//File PlayerButton.cpp

#include "PlayerButton.h"

PlayerButton::PlayerButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{}

void PlayerButton::handleClick(CommandQueue & queue) {
}

EndTurnButton::EndTurnButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton{ id, textures, pos }
{}

void EndTurnButton::handleClick(CommandQueue & queue) {
	Command command;
	command.id = commandID::SWITCHPLAYER;
	queue.push(command);
}

WonButton::WonButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton{ id, textures, pos }
{}

void WonButton::handleClick(CommandQueue & queue) {
	Command command;
	command.id = commandID::NEWGAME;
	queue.push(command);
}

