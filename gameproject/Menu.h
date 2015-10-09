//File StartButton.h

#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Enums.h"
#include "Menu.h"

class Menu {
public:
	Menu(textureID, const textureHolder& textures, sf::Vector2f);

	void setPosition(sf::Vector2f);

	sf::Vector2f getPosition();
//	void exit(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window) ;	// draw methode met position erbij	
	void handleMouse(sf::Vector2f pos, sf::RenderWindow & window);


private:
	textureID id;
	sf::Sprite menu;

	bool selected = false;
};
#endif