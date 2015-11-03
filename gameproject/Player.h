//File Player.h

#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Unit.h"
#include "CommandQueue.h"

class Player {
public:
	Player(sf::Color, bool);
	sf::Color getPlayer();
	bool getActive();
	void setActive(bool);
	int getPoints();
	void substractPoints(CommandQueue & queue);
	int getMoney();
	void setMoney(int mon);
	void setUnitSelected(bool usel);
	bool getUnitSelected();
	int getUnitAttacks();
	void setUnitAttacks(int attacks);
	void diffUnitAttacks(int attacks);

private:
	bool active;
	bool unitSelected;		// if a unit is selected
	sf::Color side;
	int points = 100;
	int money = 1000;
	int unitAttacks = 0;
};


#endif