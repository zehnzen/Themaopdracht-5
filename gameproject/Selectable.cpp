//File Selectable.cpp

#include "Selectable.h"

Selectable::Selectable()



bool Selectable::checkClicked(sf::Vector2f pos) {
	return sprite.getGlobalBounds().contains(pos);
}

void Selectable::setSelected(bool b) {
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