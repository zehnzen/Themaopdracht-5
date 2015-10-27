//File Game.h

#ifndef _GAME_H
#define _GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Terrain.h"
#include "Enums.h"
#include "Unit.h"
#include "Soldier.h"
#include "Bomber.h"
#include "Player.h"
#include "Music.h"
#include "Sound.h"
#include "MenuButton.h"


class Game {
public:
	Game();
	void run();

private:
	void processInput();
	void update(sf::Time);
	void render();
	void HUD();

	void loadMenu();

	void loadTextures();
	void makePlayfield();

	void handleKeypress(sf::Keyboard::Key, bool);
	void handleMouse(sf::Mouse::Button);
	void initText();

	void switchPlayer();
	Player getActivePlayer();

	void markField(int walklimit, sf::Vector2f position, sf::Color color);		// mark the field (1 terrain) in order to show a units walking limit
	void spawnUnit(sf::Vector2f);
	void spawnBomber(sf::Vector2f);

	sf::RenderWindow window;
	static const sf::Time timePerFrame;

	Player playerB;
	Player playerR;
	std::vector<std::unique_ptr<Unit>> unitBContainer;
	std::vector<std::unique_ptr<Unit>> unitRContainer;

	std::vector<std::unique_ptr<Terrain>> terrainContainer;
	std::vector<std::unique_ptr<MenuButton>> menuContainer;

	textureHolder textures;

	sf::Vector2f oldUnitPosition;			// nodig voor het deselecteren van de tiles
	int oldUnitWalklimit;					// nodig voor het deselecteren van de tiles

	Music music;
	Sound sound;

	bool inMenu = false;
	sf::Font font;
	sf::Text text;
};


#endif
