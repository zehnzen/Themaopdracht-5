//File MenuButton

#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "Button.h"

class MenuButton : public Button{
public:
	MenuButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	void setPosition(sf::Vector2f) override;
	sf::Vector2f getPosition() override;

	void draw(sf::RenderWindow & window);

	//TODO geeft nu int terug voor testing, moet later met commands gaan werken.
	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>> & container, Music & music);

private:
	sf::Vector2f leaveScreen = sf::Vector2f(1000, 1000);
};

#endif
