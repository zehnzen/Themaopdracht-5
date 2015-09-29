//File Unit.cpp

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "V2Functions.h"


Unit::Unit(textureID id, const textureHolder& textures, sf::Vector2f pos) :
	id{ id },
	sprite{ textures.get(id), sf::IntRect(0, 0, TILESIZE - 10, TILESIZE - 10) }
{
	setPos(pos);
	sprite.setColor(sf::Color::Blue);
}

void Unit::setTexture(sf::Texture & text) {
	sprite.setTexture(text, true);
	sprite.setTextureRect(sf::IntRect(0, 0, TILESIZE - 10, TILESIZE - 10));
}

void Unit::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos.x + 7, pos.y + 7);
}

void Unit::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Unit::draw(sf::RenderWindow & window, sf::Vector2f position) {		// draw methode met position erbij
	sprite.setPosition(position);
	window.draw(sprite);
}

void Unit::handleMouse(sf::Vector2f pos) {
	if (selected) { // als al geselecteerd dan afhandelen of hij wil lopen of toch wil afbreken)
		sprite.setColor(sf::Color::Yellow);
		// IK WIL NU DAT HIJ IN ALLE RICHTINGEN MAXIMAAL 1 VAKJE MAG VERSPRINGEN (geel is selected, ander is die, de kleur van het team)
		if ((pos.x - sprite.getPosition().x >= -TILESIZE)	&& (pos.x - sprite.getPosition().x <= 0) && ((pos.y - sprite.getPosition().y <= TILESIZE ) && (pos.y - sprite.getPosition().y >= 0))) {		// rechts
				setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));	//Lelijkste stukje code van allemaal, gaat zoveel afronding fout wss
		}
		// BIJ DEZE MAG HIJ BLIJKBAAR NOG ONBEPERKT VER NAAR BENEDEN "SPRINGEN"
		else if ((pos.x - sprite.getPosition().x <= TILESIZE * 2) && (pos.x - sprite.getPosition().x >= 0) && ((pos.y - sprite.getPosition().y <= TILESIZE) && (pos.y - sprite.getPosition().y >= 0))) {		// links
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));	//Lelijkste stukje code van allemaal, gaat zoveel afronding fout wss
		}
		else if ((pos.y - sprite.getPosition().y >= -TILESIZE) && (pos.y - sprite.getPosition().y <= 0) && ((pos.x - sprite.getPosition().x <= TILESIZE) && (pos.x - sprite.getPosition().x >= 0))) {		// omhoog
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));	//Lelijkste stukje code van allemaal, gaat zoveel afronding fout wss
		}
		else if ((pos.y - sprite.getPosition().y <= TILESIZE * 2) && (pos.y - sprite.getPosition().y >= 0) && ((pos.x - sprite.getPosition().x <= TILESIZE) && (pos.x - sprite.getPosition().x >= 0))) {		// omlaag
			setPos(V2f_from_V2i(v2i_MOD(V2i_from_V2f(pos), TILESIZE)));	//Lelijkste stukje code van allemaal, gaat zoveel afronding fout wss
		}

		selected = false;
		sprite.setColor(sf::Color::Blue);
	}
	else {		// als niet geselecteerd kijken of je hem alsnog wilt selecteren
		selected = sprite.getGlobalBounds().contains(pos);
		if (selected) {
			sprite.setColor(sf::Color::Yellow);
		}
		else {
			sprite.setColor(sf::Color::Blue);
		}
	}
}

void Unit::action() {
	// selecteerbare vakjes maken om zich heen: (straal van 1)
}
