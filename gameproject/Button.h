//Button

#ifndef _BUTTON_H
#define _BUTTON_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Enums.h"

class Button {
public:
	Button(textureID, const textureHolder& textures, sf::Vector2f);

	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();

	void draw(sf::RenderWindow & window) ;	// draw methode met position erbij
	virtual int handleMouse(sf::Vector2f pos, sf::RenderWindow & window); //TODO geeft nu int terug voor testing, moet later met commands gaan werken.


protected:
	textureID id;
	sf::Sprite button;
};
#endif