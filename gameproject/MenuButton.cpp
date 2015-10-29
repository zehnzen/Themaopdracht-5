//File MenuButton.cpp

#include "MenuButton.h"

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button{id, textures, pos}
{
	numFrames = 220;
}

void MenuButton::update(sf::Time dt) {
	sf::Time timePerFrame = duration / (float)numFrames;
	elapsedTime += dt;

	while (elapsedTime >= timePerFrame)
	{
		if(!(sprite.getPosition().x <= 50))
		sprite.setPosition(sprite.getPosition() - sf::Vector2f(1,0));
		elapsedTime -= timePerFrame;
	}
}


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
					container[i]->setPosition(sf::Vector2f(ScreenWidth, ScreenHeight));
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
					container[i]->setPosition(sf::Vector2f(ScreenWidth, ScreenHeight));
				}
			}
		}
		if (id == textureID::EXIT) {
			window.close();
		}
	}
	return 0;
}