//File MenuButton.cpp

#include "MenuButton.h"

MenuButton::MenuButton(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	Button{ id, textures, pos }
{}

int MenuButton::handleMouse(sf::Vector2f pos, sf::RenderWindow & window,
	std::vector<std::unique_ptr<MenuButton>>& container, Music & music) {
	if (sprite.getGlobalBounds().contains(pos))
	{
		if (id == textureID::START)
		{
			music.play(musicID::MISSIONTHEME);
			return 1;
		}
		if (id == textureID::OPTION)
		{
			container[1]->setPosition(leaveScreen); // container 1 = startbutton
			container[4]->setPosition(leaveScreen); //4 = optionbutton
			container[3]->setPosition(leaveScreen); //3 = exit
													//de mute[4] en backbutton[5] zaten buiten scherm dus die halen we weer binnen scherm
			container[2]->setPosition(sf::Vector2f(50, 330)); //2 = mute
			container[5]->setPosition(sf::Vector2f(50, 400)); //5 = back
		}
		if (id == textureID::EXIT)
		{
			window.close();
		}
		if (id == textureID::MUTE) {
			std::cout << "MUTE\n";
			music.togglePlaying();
		}
		if (id == textureID::BACK)
		{
			//start, option en exit button terug halen
			container[1]->setPosition(sf::Vector2f(50, 260)); // container 1 = startbutton
			container[4]->setPosition(sf::Vector2f(50, 330)); //4 = optionbutton
			container[3]->setPosition(sf::Vector2f(50, 400)); //3 = exit

			//de mute[4] en backbutton[5] zaten buiten scherm dus die halen we weer binnen scherm
			container[2]->setPosition(leaveScreen);
			container[5]->setPosition(leaveScreen);
		}

	}
	return 0;
}