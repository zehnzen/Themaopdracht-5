//File UnitButton.h

#ifndef _UNITBUTTON_H
#define _UNITBUTTON_H

#include "Button.h"
#include "Unit.h"
#include "Bomber.h"

class UnitButton : public Button {
public:
	UnitButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	virtual Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color);
};

class DragonButton : public UnitButton {
public:
	DragonButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) override;
};
#endif