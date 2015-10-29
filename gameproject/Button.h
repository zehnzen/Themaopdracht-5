//File Button.h

#ifndef _BUTTON_H
#define _BUTTON_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Enums.h"
#include "Music.h"

class Button {
public:
	Button();
	Button(textureID, const textureHolder& textures, sf::Vector2f);

	virtual void setPosition(sf::Vector2f);
	virtual sf::Vector2f getPosition() = 0;

	virtual void draw(sf::RenderWindow & window) = 0;	// draw methode met position erbij
	//virtual int handleMouse(sf::Vector2f pos, sf::RenderWindow & window); //TODO geeft nu int terug voor testing, moet later met commands gaan werken.

	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<Button>> & container, Music & music);

protected:
	textureID id;
	sf::Sprite button;

};
#endif