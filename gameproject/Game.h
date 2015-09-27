//File Game.h

#ifndef _GAME_H
#define _GAME_H

#include <SFML\Graphics.hpp>
#include "Terrain.h"
#include "Enums.h"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

	void handleInput(sf::Keyboard::Key, bool);

	sf::RenderWindow window;
	Terrain grass;
	TextureHolder textureList;
};

#endif
