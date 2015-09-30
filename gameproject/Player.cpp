//File Player.cpp

#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(sf::Color side, bool set):
	side {side},
	points {0},
	money {0},
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