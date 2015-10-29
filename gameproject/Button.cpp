//File Button.cpp

#include <SFML/Graphics.hpp>
#include "Button.h"

Button::Button(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	numFrames = 1;
	repeat = true;
}

bool Button::getClicked(sf::Vector2f pos) {
	return (sprite.getGlobalBounds().contains(pos)) ? true : false;
}

int Button::handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<Button>>& container, Music & music)
{
	return 0;
}

