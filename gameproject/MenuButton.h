//File MenuButton

#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "Button.h"
#include <array>

class MenuButton : public Button {
public:
	MenuButton(textureID, const textureHolder& textures, sf::Vector2f pos = sf::Vector2f(0,0));

	void update(sf::Time) override;
	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>> & container, Music & music);
	bool LoadedInScreen = true;

private:
	bool musicMuted = false;

	std::vector<sf::Vector2f> menuPosition = {
		{ sf::Vector2f(0, 0) },
		{ sf::Vector2f(ScreenWidth,			260) },
		{ sf::Vector2f(ScreenWidth + 40,	330) },
		{ sf::Vector2f(ScreenWidth + 80,	400) },
		{ sf::Vector2f(ScreenWidth,			330) },
		{ sf::Vector2f(ScreenWidth + 40,	400) },
	};
	std::vector<sf::Vector2f>::iterator it;  // declare an iterator to a vector of strings
	int i;
};

#endif
