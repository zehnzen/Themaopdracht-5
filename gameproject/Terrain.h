//File Terrain.h

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <SFML/Graphics.hpp>

class Terrain {
public:
	Terrain();
	void setTexture(sf::Texture & texture);
	void draw(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window, sf::Vector2f position);	// draw methode met position erbij
	
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif