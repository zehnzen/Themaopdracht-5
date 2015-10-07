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

	sf::RenderWindow window;

	Player playerB;
	Player playerR;
	std::vector<std::unique_ptr<Unit>> unitBContainer;
	std::vector<std::unique_ptr<Unit>> unitRContainer;

	//errstd::vector<std::unique_ptr<Unit>> unitContainer;
	std::vector<std::unique_ptr<Terrain>> terrainContainer;
	textureHolder	textures;
	sf::Font font;
	sf::Text text;

#endif
};