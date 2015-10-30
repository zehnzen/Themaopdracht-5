//File PlayerButton.cpp

#include "PlayerButton.h"

PlayerButton::PlayerButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{}

buttonID PlayerButton::handleClick() {
	return buttonID::NONE;
}

EndTurnButton::EndTurnButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	PlayerButton{ id, textures, pos }
{}

buttonID EndTurnButton::handleClick() {
	return buttonID::ENDTURN;
}