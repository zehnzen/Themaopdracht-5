//File Button.h

#ifndef _BUTTON_H
#define _BUTTON_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Enums.h"
#include "Music.h"
#include "GameObject.h"

class Button : public GameObject{
public:
	Button(textureID, const textureHolder& textures, sf::Vector2f);

	bool getClicked(sf::Vector2f);

	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<Button>> & container, Music & music);
};
#endif