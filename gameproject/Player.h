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
	int getUnitAttacks();
	void setUnitAttacks(int attacks);
	void diffUnitAttacks(int attacks);
	int getUnitWalks();
	void resetUnitWalks();
	void diffUnitWalks(int steps);


private:
	bool active;
	sf::Color side;
	int points = 100;
	int money = 1000;
	int unitAttacks = 0;
	int unitWalks = 0;
};


#endif