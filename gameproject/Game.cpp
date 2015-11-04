//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

/**********************************************************************************************//**
 * @fn	Game::Game() : window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML window", 1 << 2), input
 *
 * @brief	Default constructor.
 **************************************************************************************************/

Game::Game() :
	window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML window", 1 << 2),
	input{ window },
	playerB{ sf::Color::Blue, true },
	playerR{ sf::Color::Red, false }
{
	loadTextures();
	loadMenu();
	initText();
	makePlayfield();
	makeLevel();
	music.play(musicID::MENUTHEME);
	music.setVolume(7);
}

/**********************************************************************************************//**
 * @fn	void Game::initText()
 *
 * @brief	Initialises the text (sets fond, size and color).
 **************************************************************************************************/

void Game::initText() {
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
}

/**********************************************************************************************//**
 * @fn	void Game::loadMenu()
 *
 * @brief	Loads all the menubuttons into a vector.
 **************************************************************************************************/

void Game::loadMenu() {
	struct buttonVal {
		textureID id;
		sf::Vector2f pos;
	};
	inMenu = true;
	//de val1, 2 en 3 worden buiten scherm getekend(800, 100, 1200) en komen dan naar binnen bewegen
	buttonVal val1{ textureID::BACKGROUND };
	buttonVal val2{ textureID::START,		sf::Vector2f(ScreenWidth,		260) };
	buttonVal val3{ textureID::OPTION,		sf::Vector2f(ScreenWidth + 40,	330) };
	buttonVal val4{ textureID::EXIT,		sf::Vector2f(ScreenWidth + 80,	400) };
	buttonVal val5{ textureID::MUTE,		sf::Vector2f(ScreenWidth,		ScreenHeight + 10) };
	buttonVal val6{ textureID::BACK,		sf::Vector2f(ScreenWidth,		ScreenHeight + 10) };

	std::array<buttonVal, 6> menus{ val1, val2, val3, val4, val5, val6 };

	for (buttonVal value : menus) {
		std::unique_ptr<MenuButton> menubutton(new MenuButton(value.id, textures, value.pos));
		menuContainer.push_back(std::move(menubutton));
	}

	buttonVal val10{ textureID::DRAGON, sf::Vector2f(ScreenWidth - 130, ScreenHeight - 200) };
	std::unique_ptr<UnitButton> dragonButton(new DragonButton(val10.id, textures, val10.pos));
	factoryButtons.push_back(std::move(dragonButton));

	buttonVal val11{ textureID::RECRUIT, sf::Vector2f(ScreenWidth - 80, ScreenHeight - 200) };
	std::unique_ptr<UnitButton> recruitButton(new RecruitButton(val11.id, textures, val11.pos));
	factoryButtons.push_back(std::move(recruitButton));

	buttonVal val12{ textureID::SOLDIER, sf::Vector2f(ScreenWidth - 130, ScreenHeight - 150) };
	std::unique_ptr<UnitButton> soldierButton(new SoldierButton(val12.id, textures, val12.pos));
	factoryButtons.push_back(std::move(soldierButton));

	buttonVal val13{ textureID::SCOUT, sf::Vector2f(ScreenWidth - 80, ScreenHeight - 150) };
	std::unique_ptr<UnitButton> scoutButton(new ScoutButton(val13.id, textures, val13.pos));
	factoryButtons.push_back(std::move(scoutButton));

	buttonVal val20{ textureID::ENDTURN, sf::Vector2f(ScreenWidth - 120, 200) };
	std::unique_ptr<EndTurnButton> playerButton(new EndTurnButton(val20.id, textures, val20.pos));
	playerButtons.push_back(std::move(playerButton));

	wonButon = std::shared_ptr<PlayerButton>{ new WonButton{ textureID::WON, textures, sf::Vector2f{ 0,0 } } };
}

/**********************************************************************************************//**
 * @fn	void Game::loadTextures()
 *
 * @brief	Loads the textures used in the game.
 **************************************************************************************************/

void Game::loadTextures() {
	textures.load(textureID::GRASS, "images//grass.jpg");
	textures.load(textureID::ROAD, "images//road.jpg");
	textures.load(textureID::SCOUT, "images//bazookasheet.png");
	textures.load(textureID::RECRUIT, "images//unit.png");
	textures.load(textureID::DRAGON, "images//monster.png");
	textures.load(textureID::SOLDIER, "images//soldier.png");
	textures.load(textureID::FACTORY, "images//factory.png");
	textures.load(textureID::HEADQUARTER, "images//headquarter.png");
	textures.load(textureID::HOLYGRAIL, "images//holygrail.png");
	textures.load(textureID::ENDTURN, "images//endTurn.png");
	textures.load(textureID::RESOURCE, "images//resourcepoint.png");
	textures.load(textureID::BACKGROUND, "images//background.jpg");
	textures.load(textureID::START, "images//start.png");
	textures.load(textureID::OPTION, "images//option.png");
	textures.load(textureID::EXIT, "images//exit.png");
	textures.load(textureID::MUTE, "images//muteSound.png");
	textures.load(textureID::BACK, "images//back.png");
	textures.load(textureID::WON, "images//HALLO.jpg");
}

/**********************************************************************************************//**
 * @fn	void Game::makePlayfield()
 *
 * @brief	Makes the playfield used in the game.
 **************************************************************************************************/

void Game::makePlayfield() {
	for (float y = 0; y < playfieldY; y++) {
		for (float x = 0; x < playfieldX; x++) {
			std::unique_ptr<Terrain> terrain(new Terrain(textureID::GRASS, textures, sf::Vector2f{ x * TILESIZE, y * TILESIZE }));
			terrainContainer.push_back(std::move(terrain));
		}
	}
};

/**********************************************************************************************//**
 * @fn	void Game::makeLevel()
 *
 * @brief	Makes the level from a txt file.
 **************************************************************************************************/

void Game::makeLevel() {
	// 1 = niks
	// 2 = resource

	// 3 = unit blauw
	// 4 = dragon blauw
	// 5 = factory blauw
	// 6 = headquater blauw

	// 7 = unit rood
	// 8 = dragon rood
	// 9 = factory rood
	// 0 = headquarter rood

	int i = 0;
	try {
		std::ifstream input("level.txt");
		while(true) {
			char c = reader.read(input);

			switch (c) {
			case '1': break;
			case '2': spawnResource(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false);	break;
			case '3': spawnGrail(terrainContainer.at(i)->getTilePosition()); break;
				//Blauw:
			case 'a': playerB.setActive(true); playerR.setActive(false); spawnUnit(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false);	break;
			case 'b': playerB.setActive(true); playerR.setActive(false); spawnBomber(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'c': playerB.setActive(true); playerR.setActive(false); spawnSoldier(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'd': playerB.setActive(true); playerR.setActive(false); spawnFactory(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'e': playerB.setActive(true); playerR.setActive(false); spawnHQ(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
				// Rood:
			case 'z': playerB.setActive(false); playerR.setActive(true); spawnUnit(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'y': playerB.setActive(false); playerR.setActive(true); spawnBomber(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'x': playerB.setActive(false); playerR.setActive(true); spawnSoldier(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'w': playerB.setActive(false); playerR.setActive(true); spawnFactory(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			case 'v': playerB.setActive(false); playerR.setActive(true); spawnHQ(terrainContainer.at(i)->getTilePosition()); terrainContainer.at(i)->setFree(false); break;
			}
			i++;
		}
	}
	catch (endOfFile & end) {
		std::cout << end.what();
	}
	catch (std::exception & problem) {
		std::cout << problem.what();
		char c;
		std::cin >> c;
		exit(0);
	}
	playerB.setActive(true); playerR.setActive(false);
}

/**********************************************************************************************//**
 * @fn	void Game::handleLeftClick(sf::Vector2f mPosition)
 *
 * @brief	Handles the left mouseclick at a certain position.
 *
 * @param	mPosition	The position of the mouseclick.
 **************************************************************************************************/

void Game::handleLeftClick(sf::Vector2f mPosition) {
	if (matchEnd) {
		if (wonButon->getClicked(mPosition)) {
			wonButon->handleClick(cQueue);
		}
	}
	std::vector<std::unique_ptr<Unit>> * currentPlayerUnits, *enemyPlayerUnits;
	std::vector<std::unique_ptr<Building>> * currentPlayerBuildings, *enemyPlayerBuildings;
	sf::Color color;

	//------------------SET VALUES FOR WHICH TURN
	if (playerB.getActive()) {
		currentPlayerUnits = &unitBContainer;
		enemyPlayerUnits = &unitRContainer;
		currentPlayerBuildings = &buildingBContainer;
		enemyPlayerBuildings = &buildingRContainer;
		color = sf::Color::Blue;
	}
	else {
		currentPlayerUnits = &unitRContainer;
		enemyPlayerUnits = &unitBContainer;
		currentPlayerBuildings = &buildingRContainer;
		enemyPlayerBuildings = &buildingBContainer;
		color = sf::Color::Red;
	}
	//------------------END VALUES FOR WHICH TURN

	if (inMenu)
	{
		for (auto const & p : menuContainer) {
			if (p->handleMouse(mPosition, window, menuContainer, music) == 1) {//TODO test voor start
				inMenu = false;
			}
		}
	}
	else {
		for (auto const & p : playerButtons) {
			if (p->getClicked(mPosition)) {
				p->handleClick(cQueue);
			}
		}
		if (inFactory) {
			for (auto const & p : factoryButtons) {
				if (p->getClicked(mPosition)) {
					sf::Vector2f location = currentPlayerBuildings->at(factoryIndex)->getTilePosition();
					// kijken of hij wel daar mag worden gedropt
					markField(2, 2, false, location, sf::Color::Green);
					if (checkSpawn(location) != location) {
						sf::Vector2f loc = checkSpawn(location);
						// checken of de speler geld genoeg heeft:
						int cost = p->getCostMoney();
						if (((playerB.getActive()) ? playerB.getMoney() : playerR.getMoney()) >= cost) {
							(playerB.getActive()) ? playerB.setMoney(playerB.getMoney() - cost) : playerR.setMoney(playerR.getMoney() - cost);
							currentPlayerUnits->push_back(std::unique_ptr<Unit>(p->bAction(textures, loc, color)));
							(playerB.getActive()) ? playerB.diffUnitAttacks(1) : playerR.diffUnitAttacks(1);
							(playerB.getActive()) ? playerB.diffUnitWalks(1) : playerR.diffUnitWalks(1);

							for (auto const & t : terrainContainer) {
								if (t->checkClicked(loc)) {
									t->setFree(false);
								}
							}
						}
					}

					markField(2, 2, true, location, sf::Color::White);
					inFactory = false;
					break;
				}
				inFactory = false;
			}
		}		
		else {
			unitControl(mPosition, currentPlayerUnits, enemyPlayerUnits, enemyPlayerBuildings, color);
			for (const auto & p : *currentPlayerBuildings) {
				if (p->checkClicked(mPosition)) {
					std::cout << "je hebt op een factory geklikt";
					p->checkAction(cQueue);
					auto ip = std::find(currentPlayerBuildings->begin(), currentPlayerBuildings->end(), p);
					if (ip != currentPlayerBuildings->end()) {
						factoryIndex = std::distance(currentPlayerBuildings->begin(), ip);
					}
				}
			}
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::handleRightClick()
 *
 * @brief	Handles the right mouseclick.
 **************************************************************************************************/

void Game::handleRightClick() {
	switchPlayer();
}

/**********************************************************************************************//**
 * @fn	void Game::handleMouseEnter(sf::Vector2f mPosition)
 *
 * @brief	Handles the event of a mouse entering a certain position.
 *
 * @param	mPosition	The position of the mouse.
 **************************************************************************************************/

void Game::handleMouseEnter(sf::Vector2f mPosition) {
	if (inFactory) {
		for (auto const & p : factoryButtons) {
			if (p->getClicked(mPosition)) {
				onUnitButton = true;
				unitCost = p->getCostMoney();
				break;
			}
			else onUnitButton = false;
		}
	}

	else {
		for (auto const & p : resourceContainer) {
			if (p->checkClicked(mPosition)) {
				onBuildingB = false;
				onBuildingR = false;
				onResource = true;
				resourceMoney = p->getResourceMoney();
				break;
			}
			else onResource = false;
		}
		for (auto const & p : buildingBContainer) {
			if (p->checkClicked(mPosition)) {
				onResource = false;
				onBuildingR = false;
				onBuildingB = true;
				health = p->getHP();
				break;
			}
			else onBuildingB = false;
		}
		for (auto const & p : buildingRContainer) {
			if (p->checkClicked(mPosition)) {
				onResource = false;
				onBuildingB = false;
				onBuildingR = true;
				health = p->getHP();
				break;
			}
			else onBuildingR = false;
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::unitControl(sf::Vector2f mPosition, std::vector<std::unique_ptr<Unit>> * currentPlayerUnits, std::vector<std::unique_ptr<Unit>> * enemyPlayerUnits, std::vector<std::unique_ptr<Building>> * enemyPlayerBuildings, sf::Color color)
 *
 * @brief	Unit control.
 *
 * @param	mPosition						The position of the mouse.
 * @param [in,out]	currentPlayerUnits  	If non-null, the current player units.
 * @param [in,out]	enemyPlayerUnits		If non-null, the enemy player units.
 * @param [in,out]	enemyPlayerBuildings	If non-null, the enemy player buildings.
 * @param	color							The color of the current player.
 **************************************************************************************************/

void Game::unitControl(sf::Vector2f mPosition, std::vector<std::unique_ptr<Unit>> * currentPlayerUnits, std::vector<std::unique_ptr<Unit>> * enemyPlayerUnits, std::vector<std::unique_ptr<Building>> * enemyPlayerBuildings, sf::Color color) {			// het afhandelen van de movement, aanvallen en actions van de units
	if (!unitSelected) {
		markField(unitWalklimit, unitAttackrange, true, unitPosition, sf::Color::White);
		for (auto const & p : *currentPlayerUnits) {
			if (p->checkClicked(mPosition)) {
				unitSelected = true;
				allySelected = true;
				p->makeSelected(mPosition);

				auto ip = std::find(currentPlayerUnits->begin(), currentPlayerUnits->end(), p);
				if (ip != currentPlayerUnits->end()) {
					unitIndex = std::distance(currentPlayerUnits->begin(), ip);
				}

				unitPosition = p->getTilePosition();		// onthouden voor het deselecteren van de tiles
				unitWalklimit = p->getWalklimit();
				unitAttackrange = p->getAttackrange();
				markField(unitWalklimit, unitAttackrange, false, unitPosition, color);
				break;
			}
		}
		for (auto const & p : *enemyPlayerUnits) {
			if (p->checkClicked(mPosition)) {
				unitSelected = true;
				allySelected = false;

				auto ip = std::find(enemyPlayerUnits->begin(), enemyPlayerUnits->end(), p);
				if (ip != enemyPlayerUnits->end()) {
					enemyIndex = std::distance(enemyPlayerUnits->begin(), ip);
				}
				break;
			}
		}
	}
	else if (unitSelected && allySelected) {
		// lopen:
		if (checkWalk(mPosition)) {
			for (auto const & t : terrainContainer) {
				if (t->checkClicked(currentPlayerUnits->at(unitIndex)->getTilePosition())) {
					t->setFree(true);								// terrain weer vrijgeven
				}
			}
			currentPlayerUnits->at(unitIndex)->walk(mPosition);		// lopen
			for (auto const & t : terrainContainer) {
				if (t->checkClicked(mPosition)) {
					if(currentPlayerUnits->at(unitIndex)->getWalklimit() == 1) {
						(playerB.getActive()) ? playerB.diffUnitWalks(-1) : playerR.diffUnitWalks(-1);
					}
					t->setFree(false);								// terrain bezetten
				}
			}
		}
		// aanvallen enemyUnits:
		int i = 0;
		if (currentPlayerUnits->at(unitIndex)->getAttackrange() > 0) {
			for (auto const & q : *enemyPlayerUnits) {
				i++;
				if (q->checkClicked(mPosition)) {		// check of vijand wordt aangeklikt en dus of er een aanval moet komen
					if (checkAttack(mPosition)) {
						(playerB.getActive()) ? playerB.diffUnitAttacks(-1) : playerR.diffUnitAttacks(-1);
						if (q->damage(currentPlayerUnits->at(unitIndex)->attack())) {		// hij krijgt true mee als hij geen hp meer heeft, dus dan moet je hem verwijderen uit de container
							for (auto const & t : terrainContainer) {
								if (t->checkClicked(q->getTilePosition())) {
									t->setFree(true);										// terrain weer vrij maken
								}
							}
							enemyPlayerUnits->erase(enemyPlayerUnits->begin() + i - 1);
						}
					}
					break;
				}
			}
			// aanvallen Buildings:
			i = 0;
			for (auto const & q : *enemyPlayerBuildings) {
				i++;
				if (q->checkClicked(mPosition)) {
					if (checkAttack(mPosition)) {
						if (q->damage(currentPlayerUnits->at(unitIndex)->attack())) {
							for (auto const & t : terrainContainer) {
								if (t->checkClicked(q->getTilePosition())) {
									t->setFree(true);
								}
							}
							q->checkAction(cQueue);
							enemyPlayerBuildings->erase(enemyPlayerBuildings->begin() + i - 1);
						}
						(playerB.getActive()) ? playerB.diffUnitAttacks(-1) : playerR.diffUnitAttacks(-1);
					}
					break;
				}
			}

			// resources verkrijgen:
			for (auto const & r : resourceContainer) {
				if (r->checkClicked(V2f_from_V2i(sf::Mouse::getPosition(window)))) {		// check of vijand wordt aangeklikt en dus of er een aanval moet komen
					if (checkAttack(mPosition) && checkResource(mPosition, currentPlayerUnits->at(unitIndex)->getTilePosition())) {			// checken of unit naast resource staat
						(playerB.getActive()) ? playerB.diffUnitAttacks(-1) : playerR.diffUnitAttacks(-1);
						(playerB.getActive()) ? playerB.setMoney(playerB.getMoney() + r->getMoney()) : playerR.setMoney(playerR.getMoney() + r->getMoney());
						currentPlayerUnits->at(unitIndex)->resource();
					}
					break;
				}
			}
		}
		currentPlayerUnits->at(unitIndex)->setSelected(false);
		unitSelected = false;
		allySelected = false;
		unitIndex = 0;												// errorverhelpend anders raakt de HUD in de stress. info JP
		std::cout << "deselected unit\n";

		markField(unitWalklimit, unitAttackrange, true, unitPosition, sf::Color::White);
	}
	else {
		unitSelected = false;
		allySelected = false;
	}
}

/**********************************************************************************************//**
 * @fn	Player Game::getActivePlayer()
 *
 * @brief	Gets active player.
 *
 * @return	The active player.
 **************************************************************************************************/

Player Game::getActivePlayer() {
	return (playerB.getActive() ? playerB : playerR);
}

/**********************************************************************************************//**
 * @fn	void Game::switchPlayer()
 *
 * @brief	Switch player.
 **************************************************************************************************/

void Game::switchPlayer() {
	checkReckoning();
	counter += 1;
	if (counter % 2 == 0) {
		turn += 1;
	}
	std::vector<std::unique_ptr<Unit>> * units = &(playerB.getActive() ? unitBContainer : unitRContainer);
	if (unitSelected) { 
		unitSelected = false;
		markField(units->at(unitIndex)->getWalklimit(), units->at(unitIndex)->getAttackrange(), true, units->at(unitIndex)->getTilePosition(), sf::Color::White);
	}
	playerB.setActive(!playerB.getActive());
	playerB.setUnitAttacks(0);
	playerB.resetUnitWalks();
	for (auto const & p : unitBContainer) {						// alle units van B deselecteren
		p->setSelected(false);
		p->resetTurn();
		playerB.diffUnitAttacks(1);
		playerB.diffUnitWalks(1);

	}
	playerR.setActive(!playerR.getActive());
	playerR.setUnitAttacks(0);
	playerR.resetUnitWalks();
	for (auto const & p : unitRContainer) {						// alle units van R deselecteren
		p->setSelected(false);
		p->resetTurn();
		playerR.diffUnitAttacks(1);
		playerR.diffUnitWalks(1);
	}
	inFactory = false;
}

/**********************************************************************************************//**
 * @fn	void Game::spawnBomber(sf::Vector2f pos)
 *
 * @brief	Spawn bomber.
 *
 * @param	pos	The position where to spawn the bomber.
 **************************************************************************************************/

void Game::spawnBomber(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Bomber(textureID::DRAGON, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
	(playerB.getActive()) ? playerB.diffUnitAttacks(1) : playerR.diffUnitAttacks(1);
	(playerB.getActive()) ? playerB.diffUnitWalks(1) : playerR.diffUnitWalks(1);

	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::spawnUnit(sf::Vector2f pos)
 *
 * @brief	Spawn unit.
 *
 * @param	pos	The position where to spawn a unit.
 **************************************************************************************************/

void Game::spawnUnit(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Recruit(textureID::RECRUIT, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
	(playerB.getActive()) ? playerB.diffUnitAttacks(1) : playerR.diffUnitAttacks(1);
	(playerB.getActive()) ? playerB.diffUnitWalks(1) : playerR.diffUnitWalks(1);
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::spawnSoldier(sf::Vector2f pos)
 *
 * @brief	Spawn soldier.
 *
 * @param	pos	The position where to spawn a soldier.
 **************************************************************************************************/

void Game::spawnSoldier(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Soldier(textureID::SOLDIER, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
	(playerB.getActive()) ? playerB.diffUnitAttacks(1) : playerR.diffUnitAttacks(1);
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::spawnFactory(sf::Vector2f pos)
 *
 * @brief	Spawn factory.
 *
 * @param	pos	The position where to spawn a factory.
 **************************************************************************************************/

void Game::spawnFactory(sf::Vector2f pos) {
	std::unique_ptr<Building> building(new Factory(textureID::FACTORY, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? buildingBContainer.push_back(std::move(building)) : buildingRContainer.push_back(std::move(building));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::spawnHQ(sf::Vector2f pos)
 *
 * @brief	Spawn HQ.
 *
 * @param	pos	The position where to spawn a headquater.
 **************************************************************************************************/

void Game::spawnHQ(sf::Vector2f pos) {
	std::unique_ptr<Building> building(new Headquarters(textureID::HEADQUARTER, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? buildingBContainer.push_back(std::move(building)) : buildingRContainer.push_back(std::move(building));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::spawnGrail(sf::Vector2f pos)
 *
 * @brief	Spawn grail.
 *
 * @param	pos	The position where to spawn the holy grail.
 **************************************************************************************************/

void Game::spawnGrail(sf::Vector2f pos) {
	std::shared_ptr<HolyGrail> grail(new HolyGrail(textureID::HOLYGRAIL, textures, pos));
	holy = grail;
	terrainContainer.at(findTerrainIndex(pos))->setFree(false);
}

/**********************************************************************************************//**
 * @fn	void Game::spawnResource(sf::Vector2f pos)
 *
 * @brief	Spawn resource.
 *
 * @param	pos	The position where to spawn a resource.
 **************************************************************************************************/

void Game::spawnResource(sf::Vector2f pos) {
	std::unique_ptr<Resource> resource(new Resource(textureID::RESOURCE, textures, V2fModulo(pos, TILESIZE)));
	resourceContainer.push_back(std::move(resource));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

/**********************************************************************************************//**
 * @fn	bool Game::checkWalk(sf::Vector2f pos)
 *
 * @brief	Check walk.
 *
 * @param	pos	The position of the tile we want to check if we can walk to.
 *
 * @return	true if walk is possible, false if not.
 **************************************************************************************************/

bool Game::checkWalk(sf::Vector2f pos) {
	if (checkSpaceFree(pos)) {
		for (auto const & t : terrainContainer) {
			if (t->checkClicked(pos)) {
				if ((t->getColor() == sf::Color::Blue) || (t->getColor() == sf::Color::Red) || (t->getColor() == sf::Color::Green)) {
					return true;
				}
			}
		}
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	sf::Vector2f Game::checkSpawn(sf::Vector2f pos)
 *
 * @brief	Check spawn.
 *
 * @param	pos	The position of the tile we want to check if we can spawn on.
 *
 * @return	The position of a nearby terrain or our own position.
 **************************************************************************************************/

sf::Vector2f Game::checkSpawn(sf::Vector2f pos) {
	for (auto const & t : terrainContainer) {
		if ((t->getColor() == sf::Color::Green) && checkSpaceFree(t->getTilePosition())) {
			return t->getTilePosition();
		}
	}
	return pos;
}

/**********************************************************************************************//**
 * @fn	bool Game::checkAttack(sf::Vector2f pos)
 *
 * @brief	Check attack.
 *
 * @param	pos	The position where we want to check if can attack a building or a unit.
 *
 * @return	true if attack is possible, false if not.
 **************************************************************************************************/

bool Game::checkAttack(sf::Vector2f pos) {
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			if ((t->getColor() == sf::Color::Blue) || (t->getColor() == sf::Color::Red) || (t->getColor() == sf::Color::Magenta)) {
				return true;
			}
		}
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	bool Game::checkResource(sf::Vector2f pos, sf::Vector2f unitPos)
 *
 * @brief	Check resource.
 *
 * @param	pos	   	The position where we want to check if a resource is nearby.
 * @param	unitPos	The unit position.
 *
 * @return	true if a resource is nearby, false if not.
 **************************************************************************************************/

bool Game::checkResource(sf::Vector2f pos, sf::Vector2f unitPos) {
	int index = findTerrainIndex(pos);
	int uIndex = findTerrainIndex(unitPos);

	if (index - 1 == uIndex) {
		return true;
	}
	if (index + 1 == uIndex) {
		return true;
	}
	if (index - playfieldX == uIndex) {
		return true;
	}
	if (index + playfieldX == uIndex) {
		return true;
	}
	return false;
}

/**********************************************************************************************//**
 * @fn	int Game::findTerrainIndex(sf::Vector2f pos)
 *
 * @brief	Searches for the terrain index of the terrain at the given position.
 *
 * @param	pos	The position of the terrain we want to get the index of.
 *
 * @return	The found terrain index.
 **************************************************************************************************/

int Game::findTerrainIndex(sf::Vector2f pos) {
	int index = 0;
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			auto it = std::find(terrainContainer.begin(), terrainContainer.end(), t);
			if (it != terrainContainer.end()) {
				index = std::distance(terrainContainer.begin(), it);
			}
		}
	}
	return index;
}

/**********************************************************************************************//**
 * @fn	bool Game::checkSpaceFree(sf::Vector2f pos)
 *
 * @brief	Check space free.
 *
 * @param	pos	The position we want to check if the position is free.
 *
 * @return	true if free, false if not.
 **************************************************************************************************/

bool Game::checkSpaceFree(sf::Vector2f pos) {
	for (auto const & t : terrainContainer) {
		if ((t->checkClicked(pos)) && (!(t->getFree()))) {			// checken of dit terrain vakje wel vrij is
			return false;
		}
	}
	return true;
}

/**********************************************************************************************//**
 * @fn	void Game::checkReckoning()
 *
 * @brief	Check reckoning.
 **************************************************************************************************/

void Game::checkReckoning() {
	sf::Vector2f pos = holy->getTilePosition();
	sf::Color active = getActivePlayer().getPlayer();
	std::vector<std::unique_ptr<Unit>>* currentUnits = (playerB.getActive() ? &unitBContainer : &unitRContainer);
	for (auto const & unit : *currentUnits) {
		sf::Vector2f unitPos = unit->getTilePosition();
		if ((pos.x - TILESIZE == unitPos.x) && (pos.y == unitPos.y)) {
			holy->Reckoning(cQueue, active);
		}
		if ((pos.x + TILESIZE == unitPos.x) && (pos.y == unitPos.y)) {
			holy->Reckoning(cQueue, active);
		}
		if ((pos.x == unitPos.x) && (pos.y - TILESIZE == unitPos.y)) {
			holy->Reckoning(cQueue, active);
		}
		if ((pos.x == unitPos.x) && (pos.y + TILESIZE == unitPos.y)) {
			holy->Reckoning(cQueue, active);
		}
	}	
}

/**********************************************************************************************//**
 * @fn	void Game::markField(int walklimit, int attackrange, bool clear, sf::Vector2f position, sf::Color color)
 *
 * @brief	Mark field.
 *
 * @param	walklimit  	The walklimit of the unit.
 * @param	attackrange	The attackrange of the unit.
 * @param	clear	   	true to clear (sometimes we want the marked field to be cleared).
 * @param	position   	The position of the unit.
 * @param	color	   	The color of the unit.
 **************************************************************************************************/

void Game::markField(int walklimit, int attackrange, bool clear, sf::Vector2f position, sf::Color color) {					// mark the field in order to show a units walking limit
	int index = findTerrainIndex(position);
	if (clear) {
		markRange(attackrange, index, sf::Color::White);
	}
	else {
		markRange(attackrange, index, sf::Color::Magenta);
	}
	markRange(walklimit, index, color);
}

/**********************************************************************************************//**
 * @fn	void Game::markRange(int range, int index, sf::Color color)
 *
 * @brief	Mark range.
 *
 * @param	range	The range of the walk/attack of a unit.
 * @param	index	The index of the tile in the terraincontainer.
 * @param	color	The color of a unit.
 **************************************************************************************************/

void Game::markRange(int range, int index, sf::Color color) {
	range--;
	if (index >= 0 && index <= ((playfieldX * playfieldY) - 1)) {			// checken of die terrain wel bestaat			// LINKS checken
		terrainContainer.at(index)->changeColor(color);
		if (range > 0) {
			if (index % playfieldX) {
				markRange(range, index - 1, color);
			}										// RECHTS checken
			if ((index + 1) % playfieldX) {				// checken of de vakjes wel in dezelfde rij liggen
				markRange(range, index + 1, color);
			}
			if ((index - playfieldX) >= 0) {														// BOVEN checken
				markRange(range, index - playfieldX, color);
			}
			if ((index + playfieldX) <= ((playfieldX * playfieldY) - 1)) {							// ONDER hem checken
				markRange(range, index + playfieldX, color);
			}
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::run()
 *
 * @brief	Runs this object.
 **************************************************************************************************/

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			input.processInput(cQueue);
			processCommands();
			updateAnimation(timePerFrame);
		}
		render();
	}
}

/**********************************************************************************************//**
 * @fn	bool Game::getExit()
 *
 * @brief	Gets the exit.
 *
 * @return	true if exit event is true, false if not.
 **************************************************************************************************/

bool Game::getExit() {
	return gameEnd;
}

/**********************************************************************************************//**
 * @fn	void Game::processCommands()
 *
 * @brief	Process the commands.
 **************************************************************************************************/

void Game::processCommands() {
	while (!cQueue.isEmpty()) {
		Command c = cQueue.pop();
		switch (c.id) {
		case commandID::OPENMENU:
			inMenu = true;
			break;
		case commandID::LEFTCLICK:
			handleLeftClick(c.pos);
			break;
		case commandID::RIGHTCLICK:
			handleRightClick();
			break;
		case commandID::ENTERED:
			handleMouseEnter(c.pos);
			break;
		case commandID::SPAWNUNIT:
			spawnUnit(c.pos);
			break;
		case commandID::SPAWNBOMBER:
			spawnBomber(c.pos);
			break;
		case commandID::SPAWNFACTORY:
			spawnFactory(c.pos);
			break;
		case commandID::SPAWNHQ:
			spawnHQ(c.pos);
			break;
		case commandID::SPAWNRESOURCE:
			spawnResource(c.pos);
			break;
		case commandID::SWITCHPLAYER:
			switchPlayer();
			break;
		case commandID::OPENFACTORY:
			inFactory = true;
			break;
		case commandID::EXITGAME:
			window.close();
			break;
		case commandID::DMGBLUE:
			playerB.substractPoints(cQueue);
			break;
		case commandID::DMGRED:
			playerR.substractPoints(cQueue);
			break;
		case commandID::WON:
			matchEnd = true;
			break;
		case commandID::NEWGAME:
			gameEnd = false;
			window.close();
			break;
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::updateAnimation(sf::Time dt)
 *
 * @brief	Updates the animation of the sprites.
 *
 * @param	dt	The delta time used for the animation.
 **************************************************************************************************/

void Game::updateAnimation(sf::Time dt) {
	if (inMenu) {
		for (auto & p : menuContainer) {
			p->update(dt);
		}
	}
	else {
		for (auto & p : unitBContainer) {
			p->update(dt);
		}
		for (auto & p : unitRContainer) {
			p->update(dt);
		}
		for (auto & p : buildingBContainer) {
			p->update(dt);
		}
		for (auto & p : buildingRContainer) {
			p->update(dt);
		}
		for (auto & p : resourceContainer) {
			p->update(dt);
		}
		if (inFactory) {
			for (auto & p : factoryButtons) {
				p->update(dt);
			}
		}
	}
}

/**********************************************************************************************//**
 * @fn	void Game::HUD()
 *
 * @brief	Draws the HUD on the screen.
 **************************************************************************************************/

void Game::HUD() {
	text.setColor(sf::Color::Green);								//stel de tekstkleur in op de kleur van de huidige speler
	text.setString("Turn #" + std::to_string(turn));	//schrijf hoeveel health de speler heeft
	text.setPosition(ScreenWidth - 140, 250);
	window.draw(text);
	text.setColor(getActivePlayer().getPlayer());								//stel de tekstkleur in op de kleur van de huidige speler
	text.setString("Money: " + std::to_string(getActivePlayer().getMoney()));   //schrijf hoeveel geld de speler heeft
	text.setPosition(ScreenWidth - 140, 0);
	window.draw(text);
	text.setString("Health: " + std::to_string(getActivePlayer().getPoints()));	//schrijf hoeveel health de speler heeft
	text.setPosition(ScreenWidth - 140, 25);
	window.draw(text);
	text.setString("attacks: " + std::to_string(getActivePlayer().getUnitAttacks()));	//schrijf hoeveel units nog kunnen aanvallen
	text.setPosition(ScreenWidth - 140, 50);
	window.draw(text);

	text.setString("walks left: " + std::to_string(getActivePlayer().getUnitWalks()));	//schrijf hoeveel units er nog kunnen lopen
	text.setPosition(ScreenWidth - 140, 75);
	window.draw(text);


	if (unitSelected) {
		text.setPosition(ScreenWidth - 140, 100);
		std::vector<std::unique_ptr<Unit>> * units;
		if (allySelected) {
			units = &(playerB.getActive() ? unitBContainer : unitRContainer);
			text.setString(units->at(unitIndex)->getName() + ":");
			window.draw(text);
			text.setString("HP:" + std::to_string(units->at(unitIndex)->getHP()));
			text.setPosition(ScreenWidth - 140, 130);
			window.draw(text);
			text.setString("DP: " + std::to_string(units->at(unitIndex)->getDP()));
			text.setPosition(ScreenWidth - 140, 160);
		}
		else {
			playerB.getActive() ? text.setColor(playerR.getPlayer()) : text.setColor(playerB.getPlayer());
			units = &(playerB.getActive() ? unitRContainer : unitBContainer);
			text.setString(units->at(enemyIndex)->getName() + ":");
			window.draw(text);
			text.setString("HP:" + std::to_string(units->at(enemyIndex)->getHP()));
			text.setPosition(ScreenWidth - 140, 130);
			window.draw(text);
			text.setString("DP: " + std::to_string(units->at(enemyIndex)->getDP()));
			text.setPosition(ScreenWidth - 140, 160);
		}
		window.draw(text);
	}
	if (inFactory && onUnitButton) {
		text.setColor(sf::Color::Yellow);
		text.setString("cost: " + std::to_string(unitCost));
		text.setPosition(ScreenWidth - 140, 325);
		window.draw(text);
	}
	if (onBuildingB || onBuildingR) {
		text.setColor(sf::Color::Yellow);
		text.setString("HP: " + std::to_string(health));
		text.setPosition(ScreenWidth - 140, 300);
		window.draw(text);
	}
	if (onResource) {
		text.setColor(sf::Color::Yellow);
		text.setString("money: " + std::to_string(resourceMoney));
		text.setPosition(ScreenWidth - 140, 300);
		window.draw(text);
	}
}

/**********************************************************************************************//**
 * @fn	void Game::winText()
 *
 * @brief	Draws the "you suck" text on the screen after winning the game.
 **************************************************************************************************/

void Game::winText() {
	text.setPosition(sf::Vector2f{ 70, 30 });
	text.setColor(getActivePlayer().getPlayer());
	text.setString("YOU SUCK");
	text.setCharacterSize(150);
	window.draw(text);
}

/**********************************************************************************************//**
 * @fn	void Game::render()
 *
 * @brief	Renders this object.
 **************************************************************************************************/

void Game::render() {
	window.clear();
	if (inMenu) {
		for (const auto & p : menuContainer) {
			p->draw(window);
		}
	}
	else if (matchEnd) {
		wonButon->draw(window);
		winText();
	}
	else	{
		for (const auto & p : playerButtons) {
			p->draw(window);
		}
		for (const auto & p : terrainContainer) {
			p->draw(window);
		}
		for (const auto & p : unitBContainer) {
			p->draw(window);
		}
		for (const auto & p : unitRContainer) {
			p->draw(window);
		}
		for (auto & p : buildingBContainer) {
			p->draw(window);
		}
		for (auto & p : buildingRContainer) {
			p->draw(window);
		}
		for (auto & p : resourceContainer) {
			p->draw(window);
		}
		if (inFactory) {
			for (auto & p : factoryButtons) {
				p->draw(window);
			}
		}
		holy->draw(window);
		HUD();
	}
	window.display();
}