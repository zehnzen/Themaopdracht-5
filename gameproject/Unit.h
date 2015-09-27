//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include <SFML/Graphics.hpp>

class Unit{
public:
	Unit();
	void setTexture(sf::Texture & text);
	void draw(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window, sf::Vector2f position);	// draw methode met position erbij
	void handleMouse(sf::Vector2f pos);
	void Unit::action();											// dit is de actie die je unit uit kan voeren


private:
	sf::Sprite sprite;
	sf::Texture texture;
	bool selected = false;
};

#endif