//File Unit.h

#ifndef _UNIT_H
#define _UNIT_H

#include <SFML/Graphics.hpp>

class Unit{
public:
	Unit();
	void setText(sf::Texture & texture);
	void draw(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window, sf::Vector2f position);	// draw methode met position erbij

private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif