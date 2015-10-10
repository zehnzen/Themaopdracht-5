//File MenuButton.cpp

#include "MenuButton.h"

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos):
	Button(id, textures, pos)
{}

int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window) {
	if (button.getGlobalBounds().contains(pos))
	{
		if (id == textureID::START)
		{
			return 1;
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
	return 0;
}