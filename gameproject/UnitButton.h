//File UnitButton.h

#ifndef _UNITBUTTON_H
#define _UNITBUTTON_H

#include "Button.h"
#include "Unit.h"
#include "SubUnits.h"

class UnitButton : public Button {
public:
	virtual Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color);

	int getCostMoney();

	void handleMouse();

protected:
	UnitButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	int cost = 100;
};

//---------------------------------------------------------------------------------------------------
class RecruitButton : public UnitButton {
public:
	RecruitButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) override;
};

//---------------------------------------------------------------------------------------------------
class DragonButton : public UnitButton {
public:
	DragonButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) override;
};

//---------------------------------------------------------------------------------------------------
class SoldierButton : public UnitButton {
public:
	SoldierButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) override;
};

//---------------------------------------------------------------------------------------------------
class ScoutButton : public UnitButton {
public:
	ScoutButton(textureID, const textureHolder& textures, sf::Vector2f pos);

	Unit* bAction(const textureHolder& textures, sf::Vector2f pos, sf::Color color) override;
};
#endif