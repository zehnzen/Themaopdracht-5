//File MenuButton.cpp

#include "MenuButton.h"

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos):
	id{ id },
	button{ textures.get(id) },
	position{pos}
{
	setPosition(pos);
}

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Vector2f direction):
	id{ id },
	button{ textures.get(id) },
	position{ pos },
	direction{ direction }
{
	setPosition(pos);
}

void MenuButton::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);
}

void MenuButton::update(float t) {
	button.setPosition(button.getPosition() + t * direction);
}
/*
void MenuButton::changeDirection(sf::Vector2f cD) {
	direction = cD;
}*/

sf::Vector2f MenuButton::getPosition() {
	return button.getPosition();
}

void MenuButton::draw(sf::RenderWindow & window) {
	window.draw(button);
}

int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>>& container, Music & music) {

	if (button.getGlobalBounds().contains(pos)) {
		if (id == textureID::START) {
			music.play(musicID::MISSIONTHEME);
			return 1;
		}
		if (id == textureID::OPTION) {
			container[4]->setPosition(sf::Vector2f(MenuPos2));
			container[5]->setPosition(sf::Vector2f(MenuPos3));
			for (int i = 1; i <= 3; ++i) {

				container[i]->setPosition(outOfScreen);
			}

			/*	if (!musicMuted ) {
				musicMuted = true;
				music.setVolume(0);
				}
				else if(musicMuted) {
				music.setVolume(10);
				musicMuted = false;
				}
			}
		*/

		}

		if (id == textureID::MUTE) {
			std::cout << "MUTE\n";
			music.togglePlaying();
		}

		if (id == textureID::BACK) {
			container[1]->setPosition(sf::Vector2f(MenuPos1)); // container 1 = startbutton
			container[2]->setPosition(sf::Vector2f(MenuPos2)); //2 = optionbutton
			container[3]->setPosition(sf::Vector2f(MenuPos3)); //3 = exit
			container[4]->setPosition(outOfScreen);
			container[5]->setPosition(outOfScreen);
		}
	}
	return 0;

}