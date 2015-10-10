//File MenuButton

#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "Button.h"

class MenuButton : public Button {
public:
	MenuButton(textureID, const textureHolder& textures, sf::Vector2f);
	//TODO geeft nu int terug voor testing, moet later met commands gaan werken.
	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window) override;

private:

};

#endif
