//File MenuButton.cpp

#include "MenuButton.h"

MenuButton::MenuButton(textureID id, const textureHolder& textures) :
	id{ id },
	button{ textures.get(id) }
{
	setPosition(sf::Vector2f(0, 0));
}

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Vector2f direction) :
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

void MenuButton::changeDirection(sf::Vector2f cD) {
	direction = cD;
}

sf::Vector2f MenuButton::getPosition() {
	return button.getPosition();
}

void MenuButton::draw(sf::RenderWindow & window) {
	window.draw(button);
}

int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>>& container, Music & music) {

	if (button.getGlobalBounds().contains(pos)) {
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
					container[i]->LoadedInScreen = true;
					container[i]->changeDirection(vertical);
					//container[i]->setPosition(outOfScreen);
				}
				else {
					container[i]->LoadedInScreen = false;
					container[i]->changeDirection(horizontal);
					container[i]->setPosition(menuPosition[i]);
				}
			}
			/*			container[1]->setPosition(sf::Vector2f(outOfScreen)); // container 1 = startbutton
			container[2]->setPosition(sf::Vector2f(outOfScreen)); //2 = optionbutton
			container[3]->setPosition(sf::Vector2f(outOfScreen)); //3 = exit
			container[4]->setPosition(sf::Vector2f(MenuPos2));
			container[5]->setPosition(sf::Vector2f(MenuPos3));*/
		}

		if (id == textureID::MUTE) {
			std::cout << "MUTE\n";
			music.togglePlaying();
		}

		if (id == textureID::BACK) {

			for (it = menuPosition.begin(); it < menuPosition.end() - 1; ++it, ++i) {

				if (i <= 3) {
					container[i]->LoadedInScreen = false;
					container[i]->changeDirection(horizontal);
					container[i]->setPosition(menuPosition[i]);
				}
				else {
					container[i]->LoadedInScreen = true;
					container[i]->changeDirection(vertical);
					//container[i]->setPosition(outOfScreen);
				}
			}
		}
		/*			container[1]->setPosition(sf::Vector2f(MenuPos1)); // container 1 = startbutton
		container[2]->setPosition(sf::Vector2f(MenuPos2)); //2 = optionbutton
		container[3]->setPosition(sf::Vector2f(MenuPos3)); //3 = exit
		container[4]->setPosition(outOfScreen);
		container[5]->setPosition(outOfScreen);
		}*/
		if (id == textureID::EXIT) {
			window.close();
		}
	}
	return 0;

}