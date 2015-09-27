//File Game.h

#ifndef _GAME_H
#define _GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Terrain.h"
#include "Enums.h"

class Game {
public:
	Game();
	void makePlayfield();
	void run();

private:
	void processEvents();
	void update();
	void render();

	void loadTextures();

	void handleInput(sf::Keyboard::Key, bool);

	sf::RenderWindow window;
	Terrain grass;

	textureHolder	textures;
};

#endif
