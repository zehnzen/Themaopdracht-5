//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"
#include "Terrain.h"


Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos, sf::Color color) :
	Entity( id, textures),
	side {color}
{
	setPos(pos);
	sprite.setColor(color);
}

void Unit::setPos(sf::Vector2f pos) {
	//sprite.setPosition(pos.x + SpriteOffset, pos.y + SpriteOffset);
	sprite.setPosition(pos.x, pos.y);
}

void Unit::update(sf::Time dt) {

}

sf::Vector2f Unit::getTilePosition() {
	sf::Vector2f pos = sprite.getPosition();
	return sf::Vector2f(pos.x - SpriteOffset, pos.y - SpriteOffset);
}

int Unit::getWalklimit() {
	return walklimit;
}

void Unit::handleMouse(sf::Vector2f pos) {
	if (selected) { // als al geselecteerd dan afhandelen of hij wil lopen of toch wil afbreken)
		sprite.setColor(sf::Color::Yellow);
		sf::Vector2f spritePos = sprite.getPosition();
		if ((pos.x - spritePos.x >= -TILESIZE * walklimit)	&& (pos.x - spritePos.x <= 0) && ((pos.y - spritePos.y <= TILESIZE ) && (pos.y - spritePos.y >= 0))) {		// rechts
				setPos(V2fModulo(pos, TILESIZE));
		}
		else if ((pos.x - spritePos.x <= TILESIZE * walklimit + TILESIZE) && (pos.x - spritePos.x >= 0) && ((pos.y - spritePos.y <= TILESIZE) && (pos.y - spritePos.y >= 0))) {		// links
			setPos(V2fModulo(pos, TILESIZE));
		}
		else if ((pos.y - spritePos.y >= -TILESIZE * walklimit) && (pos.y - spritePos.y <= 0) && ((pos.x - spritePos.x <= TILESIZE) && (pos.x - spritePos.x >= 0))) {		// omhoog
			setPos(V2fModulo(pos, TILESIZE));
		}
		else if ((pos.y - spritePos.y <= TILESIZE * walklimit + TILESIZE) && (pos.y - spritePos.y >= 0) && ((pos.x - spritePos.x <= TILESIZE) && (pos.x - spritePos.x >= 0))) {		// omlaag
			setPos(V2fModulo(pos, TILESIZE));
		}

		selected = false;
		sprite.setColor(side);
	}
	else {		// als niet geselecteerd kijken of je hem alsnog wilt selecteren
		setSelected(sprite.getGlobalBounds().contains(pos));
	}
}

void Unit::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
	//for (int i = 0; i < walklimit; i++) {
		// vakjes tekenen
		// Terrain.changeColor(sf::Color::Green);
	//}
}

void Unit::setSelected(bool sel) {
	selected = sel;
	if (selected) {
		sprite.setColor(sf::Color::Yellow);
	}
	else {
		sprite.setColor(side);
	}
}

bool Unit::getSelected() {
	return selected;
}
