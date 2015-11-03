//File Resource.cpp

#include "Resource.h"

Resource::Resource(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	GameObject(id, textures, pos)
{
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE, TILESIZE));
	repeat = true;

	setPosition(pos);
	numFrames = 1;
}

int Resource::getResourceMoney() {
	return resourceMoney;
}

bool Resource::damage(int points) {
	hitpoints = hitpoints - points;
	if (hitpoints <= 0) {
		hitpoints = 0;
		return true;
	}
	return false;
}

bool Resource::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

void Resource::setSelected(bool b) {
	selected = b;
}

void Resource::setOldSelected(bool b) {
	oldSelected = b;
}

bool Resource::getSelected() {
	return selected;
}

bool Resource::makeSelected(sf::Vector2f pos) {
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

int Resource::getMoney() {
	int earned = 20;
	if (resourceMoney > 0) {
		earned = 100;
		resourceMoney -= earned;
	}
	if(resourceMoney <= 0) {
		sprite.setColor(sf::Color::Black);
	}
	return earned;
}