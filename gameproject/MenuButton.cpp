//File MenuButton.cpp

#include "MenuButton.h"

/**********************************************************************************************//**
 * @fn	MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the MenuButton.
 * @param	textures	The textures of the MenuButton.
 * @param	pos			The position of the MenuButton on the screen.
 **************************************************************************************************/

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button{id, textures, pos}
{
	numFrames = 300;
}

/**********************************************************************************************//**
 * @fn	void MenuButton::update(sf::Time dt)
 *
 * @brief	Makes animation of the sprites possible.
 *
 * @param	dt	The delta time.
 **************************************************************************************************/

void MenuButton::update(sf::Time dt) {
	sf::Time timePerFrame = duration / (float)numFrames;
	elapsedTime += dt;
	while (elapsedTime >= timePerFrame)
	{
		if (LoadedInScreen && sprite.getPosition().x > 50) {
			sprite.setPosition(sprite.getPosition() - sf::Vector2f(2, 0));
		}
		if (!(LoadedInScreen) && sprite.getPosition().y < ScreenHeight) {
			sprite.setPosition(sprite.getPosition() - sf::Vector2f(0, -5));
			elapsedTime -= timePerFrame;
		}
		elapsedTime -= timePerFrame;
	}
}

/**********************************************************************************************//**
 * @fn	int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>>& container, Music & music)
 *
 * @brief	Handles the mouse events.
 *
 * @param	pos				 	The position of the mouse.
 * @param [in,out]	window   	The window of the game.
 * @param [in,out]	container	The container of the mousebuttons.
 * @param [in,out]	music	 	The music.
 *
 * @return	An int.
 **************************************************************************************************/

int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>>& container, Music & music) {

	if (sprite.getGlobalBounds().contains(pos)) {
		i = 1;
		if (id == textureID::START) {
			std::cout << "START\n";
			music.play(musicID::MISSIONTHEME);
			return 1;
		}

		if (id == textureID::OPTION) {
			std::cout << "option\n" << std::endl;
			for (it = menuPosition.begin(); it < menuPosition.end() - 1; ++it, ++i) {
				// i+1 omdat hij background moet overslaan
				if (i <= 3) {
					container[i]->LoadedInScreen = false;
				}
				else {
					container[i]->LoadedInScreen = true;
					container[i]->setPosition(menuPosition[i]);
				}
			}
		}

		if (id == textureID::MUTE) {
			std::cout << "MUTE\n";
			music.togglePlaying();
		}

		if (id == textureID::BACK) {

			for (it = menuPosition.begin(); it < menuPosition.end() - 1; ++it, ++i) {

				if (i <= 3) {
					container[i]->LoadedInScreen = true;
					container[i]->setPosition(menuPosition[i]);
				}
				else {
					container[i]->LoadedInScreen = false;
				}
			}
		}
		if (id == textureID::EXIT) {
			window.close();
		}
	}
	return 0;
}