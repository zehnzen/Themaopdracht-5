//File Game.h

#ifndef _GAME_H
#define _GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Terrain.h"
#include "Enums.h"
#include "Unit.h"
#include "Player.h"
#include "Music.h"
#include "Sound.h"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();
	void HUD();

	void loadTextures();
	void makePlayfield();

	void handleInput(sf::Keyboard::Key, bool);
	void handleMouse(sf::Mouse::Button);
	void initText();

	void switchPlayer();
	Player getActivePlayer();

	void markField();		// mark the field (1 terrain) in order to show a units walking limit

	sf::RenderWindow window;

	Player playerB;
	Player playerR;
	std::vector<std::unique_ptr<Unit>> unitBContainer;
	std::vector<std::unique_ptr<Unit>> unitRContainer;

	std::vector<std::unique_ptr<Terrain>> terrainContainer;
	textureHolder	textures;

	Music music;
	Sound sound;

	sf::Font font;
	sf::Text text;

#endif
};
