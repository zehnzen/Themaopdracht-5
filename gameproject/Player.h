//File Player.h

#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Unit.h"

class Player {
public:
	Player(sf::Color, bool);
	sf::Color getPlayer();
	bool getActive();
	void setActive(bool);
	int getPoints();
	//void diffPoints(int);
	int getMoney();
	//void diffMoney(int);


private:
	bool active;
	sf::Color side;
	int points = 100;
	int money = 1000;
};


#endif