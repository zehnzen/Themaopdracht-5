//File MenuButton

#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "Button.h"

class MenuButton{
public:
	MenuButton(textureID, const textureHolder& textures, sf::Vector2f pos);
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition() ;
	void draw(sf::RenderWindow & window);	// draw methode met position erbij	
	//TODO geeft nu int terug voor testing, moet later met commands gaan werken.
	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>> & container, Music & music);

private:
	sf::Vector2f leaveScreen = sf::Vector2f(1000, 1000);
	textureID id;
	sf::Sprite button;
	bool musicStopped = false;
};

#endif
