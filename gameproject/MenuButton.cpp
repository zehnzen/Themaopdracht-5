//File MenuButton.cpp

#include "MenuButton.h"

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos):
	id{ id },
	button{ textures.get(id) }
{
	setPosition(pos);
}

void MenuButton::setPosition(sf::Vector2f pos) {
	button.setPosition(pos);
}

sf::Vector2f MenuButton::getPosition() {
	return button.getPosition();
}

void MenuButton::draw(sf::RenderWindow & window)
{
	window.draw(button);
}

int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window,
	std::vector<std::unique_ptr<MenuButton>>& container, Music & music) {
	if (button.getGlobalBounds().contains(pos))
	{
		if (id == textureID::START)
		{
			music.play(musicID::MISSIONTHEME);
			music.setVolume(7);
			return 1;
		}
		if (id == textureID::OPTION)
		{
			std::cout << "test" ;

			container[1]->setPosition(leaveScreen); // container 1 = startbutton
			container[2]->setPosition(leaveScreen); //2 = optionbutton
			container[3]->setPosition(leaveScreen); //3 = exit
													//de mute[4] e5n backbutton[5] zaten buiten scherm dus die halen we weer binnen scherm
			container[4]->setPosition(sf::Vector2f(50, 330)); //4 = mute
			container[5]->setPosition(sf::Vector2f(50, 400)); //5 = back
		}
		if (id == textureID::EXIT)
		{
			window.close();
		}
		if (id == textureID::MUTE) {
			std::cout << "MUTE\n";
			//werkt wel maar klopt(logisch) niet
			if (!musicStopped)
			{
				musicStopped = true;
				music.setVolume(10);
			}
			else if (musicStopped) {
				music.setVolume(0);
				musicStopped = false;
			}
			//de codes hieronder zou eigenlijk moeten werken ..
			/*if (!musicStopped ) {
			musicStopped = true;
			music.setVolume(0);
			}
			else if(musicStopped) {
			music.setVolume(10);
			musicStopped = false;
			}*/
		}
		if (id == textureID::BACK)
		{
			//start, option en exit button terug halen
			container[1]->setPosition(sf::Vector2f(50, 260)); // container 1 = startbutton
			container[2]->setPosition(sf::Vector2f(50, 330)); //2 = optionbutton
			container[3]->setPosition(sf::Vector2f(50, 400)); //3 = exit

			//de mute[4] en backbutton[5] zaten buiten scherm dus die halen we weer binnen scherm
			container[4]->setPosition(leaveScreen);
			container[5]->setPosition(leaveScreen);
		}

	}
	return 0;
}