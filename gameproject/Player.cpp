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

void Player::substractPoints(CommandQueue & queue) {
	points -= 10; //Momenteel de standaard value die per unit rond de resource van de vijand wordt afgetrokken.
	if (points <= 0) {
		Command command;
		command.id = commandID::WON;
		queue.push(command);
	}
}

int Player::getMoney() {
	return money;
}

void Player::setMoney(int mon) {
	money = mon;
}

int Player::getUnitAttacks() {
	return unitAttacks;
}
void Player::setUnitAttacks(int attacks) {
	unitAttacks = attacks;
}

void Player::diffUnitAttacks(int attacks) {
	unitAttacks += attacks;
}

int Player::getUnitWalks() {
	return unitWalks;
}
void Player::resetUnitWalks() {
	unitWalks = 0;
}
void Player::diffUnitWalks(int steps) {
	unitWalks += steps;
}