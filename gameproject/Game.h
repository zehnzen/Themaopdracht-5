//File Game.h

#ifndef _GAME_H
#define _GAME_H

#include <SFML\Graphics.hpp>
#include "InputHandler.h"
#include "CommandQueue.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Terrain.h"
#include "Enums.h"
#include "Unit.h"
#include "Soldier.h"
#include "Bomber.h"
#include "Building.h"
#include "Player.h"
#include "Music.h"
#include "Sound.h"
#include "MenuButton.h"
#include "UnitButton.h"
#include "PlayerButton.h"
#include "Resource.h"
#include "ReadInput.h"
#include "HolyGrail.h"

class Game {
public:
	Game();
	void run();
	bool getExit();

private:
	void processCommands();
	void updateAnimation(sf::Time);
	void render();
	void HUD();
	void winText();

	void loadMenu();

	void loadTextures();
	void makePlayfield();
	void Game::makeLevel();			// maakt het level speelklaar door units en buildings op hun plek te zetten.

	void handleLeftClick(sf::Vector2f);
	void handleRightClick();
	void handleMouseEnter(sf::Vector2f);
	void initText();

	void switchPlayer();
	Player getActivePlayer();

	void unitControl(sf::Vector2f, std::vector<std::unique_ptr<Unit>> * cPUnits, std::vector<std::unique_ptr<Unit>> * ePUnits, std::vector<std::unique_ptr<Building>> * ePBuildings, sf::Color color);		// afhandeling van de acties van de units

	void markField(int walklimit, int attackrange, bool clear, sf::Vector2f position, sf::Color color);		// mark the field (1 terrain) in order to show a units walking limit
	void markRange(int range, int index, sf::Color color);

	bool checkWalk(sf::Vector2f);		// aan de hand van de markering van de tiles kijken of een unit mag lopen
	sf::Vector2f checkSpawn(sf::Vector2f pos);
	bool checkAttack(sf::Vector2f);
	bool checkResource(sf::Vector2f, sf::Vector2f);

	int findTerrainIndex(sf::Vector2f);

	void spawnUnit(sf::Vector2f);
	void spawnBomber(sf::Vector2f);
	void spawnSoldier(sf::Vector2f);
	void spawnFactory(sf::Vector2f);
	void spawnHQ(sf::Vector2f);
	void spawnResource(sf::Vector2f);
	void spawnGrail(sf::Vector2f);

	bool checkSpaceFree(sf::Vector2f pos);		// checken of plek vrij is zodat de units weten of ze hierheen zouden kunnen verplaatsen
	void checkReckoning();

	sf::RenderWindow window;
	InputHandler input;
	CommandQueue cQueue;
	static const sf::Time timePerFrame;

	Player playerB;
	Player playerR;
	std::shared_ptr<HolyGrail> holy;
	std::vector<std::unique_ptr<Unit>> unitBContainer;
	std::vector<std::unique_ptr<Unit>> unitRContainer;

	std::vector<std::unique_ptr<Building>> buildingBContainer;
	std::vector<std::unique_ptr<Building>> buildingRContainer;

	std::vector<std::unique_ptr<Resource>> resourceContainer;

	std::vector<std::unique_ptr<Terrain>> terrainContainer;
	std::vector<std::unique_ptr<MenuButton>> menuContainer;

	std::vector<std::unique_ptr<UnitButton>> factoryButtons;

	std::vector<std::unique_ptr<PlayerButton>> playerButtons;
	std::shared_ptr<PlayerButton> wonButon;

	textureHolder textures;

	sf::Vector2f unitPosition;			// nodig voor het deselecteren van de tiles
	int unitWalklimit;					// nodig voor het deselecteren van de tiles
	int unitAttackrange;
	bool unitSelected = false;
	bool allySelected = false;
	int unitIndex;
	int factoryIndex;

	Music music;
	Sound sound;

	bool inMenu = false;
	bool inFactory = false;
	bool onUnitButton = false;

	int unitCost = 0;
	bool matchEnd = false;
	bool gameEnd = true;

	sf::Font font;
	sf::Text text;

	int playfieldX = 18;
	int playfieldY = 11;

	ReadInput reader;
};


#endif
