//File Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(sf::Color side, bool set):
	side {side},
	active{set}
{}

sf::Color Player::getPlayer() {
	return side;
}

bool Player::getActive() {
	return active;
}

void Player::setActive(bool set) {
	active = set;
}

int	Player::getPoints() {
	return points;
}

int Player::getMoney() {
	return money;
}

void Player::setUnitSelected(bool usel) {
	unitSelected = usel;
}

bool Player::getUnitSelected() {
	return unitSelected;
}