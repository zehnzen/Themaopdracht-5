//File UnitButton.h

#ifndef _UNITBUTTON_H
#define _UNITBUTTON_H

#include "Button.h"
#include "Unit.h"
#include "Bomber.h"
#include "Soldier.h"

class UnitButton : public Button {
public:
	UnitButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	virtual Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale);

	int getCostMoney();

	void handleMouse();

protected:
	int cost = 100;
};

//---------------------------------------------------------------------------------------------------
class DragonButton : public UnitButton {
public:
	DragonButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) override;
};

//---------------------------------------------------------------------------------------------------
class SoldierButton : public UnitButton {
public:
	SoldierButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color, float scale) override;
};
#endif