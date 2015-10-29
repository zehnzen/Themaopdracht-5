//File Button.cpp

#include <SFML/Graphics.hpp>
#include "Button.h"

Button::Button()
{
}

Button::Button(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	id{ id },
	button{ textures.get(id) }
{
	setPosition(pos);
}

void Button::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);
}

sf::Vector2f Button::getPosition()
{
	return button.getPosition();
}

void Button::draw(sf::RenderWindow & window) {
	window.draw(button);
}
//TODO temporary communication
/*int Button::handleMouse(sf::Vector2f pos, sf::RenderWindow & window)
{
	return 0;
}*/
int Button::handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<Button>>& container, Music & music)
{
	return 0;
}

