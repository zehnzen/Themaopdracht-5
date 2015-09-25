//File Terrain.h

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <SFML/Graphics.hpp>

class Terrain {
public:
	Terrain();
	void setText(sf::Texture & texture);
	void draw(sf::RenderWindow & window);
	
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif