//File Menu.cpp

#include <SFML/Graphics.hpp>
#include "Menu.h"

Menu::Menu(textureID id, const textureHolder & textures, sf::Vector2f pos) :
	id{ id },
	menu{ textures.get(id) }
{
	setPosition(pos);
}

void Menu::setPosition(sf::Vector2f pos) {
	menu.setPosition(pos);
}
/*
void Menu::moveOutScreen(sf::Vector2f pos) :
	menu { textures.get(id) }
{
	menu.setPosition(pos);
}
*/

sf::Vector2f Menu::getPosition()
{
	return menu.getPosition();
}

void Menu::draw(sf::RenderWindow & window) {
	window.draw(menu);
}

void Menu::handleMouse(sf::Vector2f pos, sf::RenderWindow & window)
{
	if (menu.getGlobalBounds().contains(pos))
	{
		if (id == textureID::START)
		{
			std::cout << "balbabl";
		}
		if (id == textureID::OPTION)
		{
		}
		if (id == textureID::EXIT)
		{
			window.close();
		}
		if (id == textureID::MUTE)
		{
		}
		if (id == textureID::BACK)
		{
		}
	}
}
