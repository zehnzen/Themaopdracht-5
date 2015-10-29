//File PlayerObject.cpp

#include "PlayerObject.h"

PlayerObject::PlayerObject(textureID id, const textureHolder & textures, sf::Vector2f pos, sf::Color color):
	GameObject(id, textures, pos),
	side{ color }
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	sprite.setColor(color);
	repeat = true;
}

int PlayerObject::getHP() {
	return hitpoints;
}

bool PlayerObject::damage(int points) {
	hitpoints = hitpoints - points;
	if (hitpoints <= 0) {
		hitpoints = 0;
		return true;
	}
	return false;
}

bool PlayerObject::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

void PlayerObject::setSelected(bool b) {
	selected = b;
	if (selected) {
		sprite.setColor(sf::Color::Yellow);
	}
	else {
		sprite.setColor(side);
	}
}

void PlayerObject::setOldSelected(bool b) {
	oldSelected = b;
}

bool PlayerObject::getSelected() {
	return selected;
}

bool PlayerObject::makeSelected(sf::Vector2f pos) {
	setSelected(sprite.getGlobalBounds().contains(pos));
	if (selected) {
		if (oldSelected == false) {
			oldSelected = true;
		}
		else {
			selected = false;
			oldSelected = false;
		}
	}
	return selected;
}