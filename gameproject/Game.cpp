//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :
	window	(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML window", 1 << 2),
	input	{window},
	playerB	{ sf::Color::Blue, true},
	playerR	{ sf::Color::Red, false}
	{
		loadTextures();
		loadMenu();
		initText();
		makePlayfield();
		music.play(musicID::MENUTHEME);
		music.setVolume(7);
}

void Game::initText() {
	font.loadFromFile("arial.ttf");
	// Create a text
	text.setString("standaardtekst, graag vervangen");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
}

void Game::loadMenu() {
	struct buttonVal {
		textureID id;
		sf::Vector2f pos;
		sf::Vector2f movingDirection;
	};
	inMenu = true;
	//de val1, 2 en 3 worden buiten scherm getekend(800, 100, 1200) en komen dan naar binnen bewegen
	buttonVal val1{ textureID::BACKGROUND };
	buttonVal val2{ textureID::START,		sf::Vector2f(ScreenWidth,		260) };
	buttonVal val3{ textureID::OPTION,		sf::Vector2f(ScreenWidth + 40,	330) };
	buttonVal val4{ textureID::EXIT,		sf::Vector2f(ScreenWidth + 80,	400) };
	buttonVal val5{ textureID::MUTE,		sf::Vector2f(ScreenWidth,		ScreenHeight + 10) };
	buttonVal val6{ textureID::BACK,		sf::Vector2f(ScreenWidth,	ScreenHeight + 10) };

	std::array<buttonVal, 6> menus{ val1, val2, val3, val4, val5, val6 };

	for (buttonVal value : menus) {
		std::unique_ptr<MenuButton> menubutton(new MenuButton(value.id, textures, value.pos));
		menuContainer.push_back(std::move(menubutton));
	}

	buttonVal val10{ textureID::DRAGON, sf::Vector2f(500, 400) };
	std::unique_ptr<UnitButton> dragonButton(new DragonButton(val10.id, textures, val10.pos));
	factoryButtons.push_back(std::move(dragonButton));

	buttonVal val11{ textureID::UNIT, sf::Vector2f(550, 400) };
	std::unique_ptr<UnitButton> unitButton(new UnitButton(val11.id, textures, val11.pos));
	factoryButtons.push_back(std::move(unitButton));

	buttonVal val20{ textureID::ENDTURN, sf::Vector2f(50, 410) };
	std::unique_ptr<EndTurnButton> playerButton(new EndTurnButton(val20.id, textures, val20.pos));
	playerButtons.push_back(std::move(playerButton));
}

void Game::loadTextures() {

	textures.load(textureID::GRASS, "images//grass.jpg");
	textures.load(textureID::ROAD, "images//road.jpg");
	textures.load(textureID::UNIT, "images//unit.jpg");
	textures.load(textureID::DRAGON, "images//dragon.png");
	textures.load(textureID::FACTORY, "images//factory2.png");
	textures.load(textureID::HEADQUARTER, "images//headquarter.jpg");
	textures.load(textureID::ENDTURN, "images//endTurn.png");
	textures.load(textureID::RESOURCE, "images//resourcepoint.png");
	textures.load(textureID::BACKGROUND, "images//background.jpg");
	textures.load(textureID::START, "images//start.png");
	textures.load(textureID::OPTION, "images//option.png");
	textures.load(textureID::EXIT, "images//exit.png");
	textures.load(textureID::MUTE, "images//muteSound.png");
	textures.load(textureID::BACK, "images//back.png");
}

void Game::makePlayfield() {
	for (float y = 0; y < playfieldY; y++) {
		for (float x = 0; x < playfieldX; x++) {
			if (x == 3 || x == 6) {
				std::unique_ptr<Terrain> terrain(new Terrain(textureID::ROAD, textures, sf::Vector2f{ x * TILESIZE, y * TILESIZE }));
				terrainContainer.push_back(std::move(terrain));
			}
			else {
				std::unique_ptr<Terrain> terrain(new Terrain(textureID::GRASS, textures, sf::Vector2f{ x * TILESIZE, y * TILESIZE }));
				terrainContainer.push_back(std::move(terrain));
			}
		}
	}
};

void Game::handleLeftClick(sf::Vector2f mPosition) {
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
				if (p->handleClick() == buttonID::ENDTURN) {
					switchPlayer();
				}
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

void Game::handleRightClick() {
	switchPlayer();
}

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

				auto ip = std::find(currentPlayerUnits->begin(), currentPlayerUnits->end(), p);
				if (ip != currentPlayerUnits->end()) {
					unitIndex = std::distance(currentPlayerUnits->begin(), ip);

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
					t->setFree(false);								// terrain bezetten
				}
			}
		}
		// aanvallen enemyUnits:
		int i = 0;
		for (auto const & q : *enemyPlayerUnits) {
			i++;
			if (q->checkClicked(mPosition)) {		// check of vijand wordt aangeklikt en dus of er een aanval moet komen
				if (checkAttack(mPosition)) {
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
				}
				break;
			}
		}

		// resources verkrijgen:
		for (auto const & r : resourceContainer) {
			if (r->checkClicked(V2f_from_V2i(sf::Mouse::getPosition(window)))) {		// check of vijand wordt aangeklikt en dus of er een aanval moet komen
				if (checkAttack(mPosition) && currentPlayerUnits->at(unitIndex)->getAttackrange() > 0) {			// checken of de resource niet uitgeput is
					(playerB.getActive()) ? playerB.setMoney(playerB.getMoney() + r->getMoney()) : playerR.setMoney(playerR.getMoney() + r->getMoney());
					currentPlayerUnits->at(unitIndex)->resource();
				}
				break;
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

Player Game::getActivePlayer() {
	return (playerB.getActive() ? playerB : playerR);
}

void Game::switchPlayer() {
	std::vector<std::unique_ptr<Unit>> * units = &(playerB.getActive() ? unitBContainer : unitRContainer);
	if (unitSelected) { 
		unitSelected = false;
		markField(units->at(unitIndex)->getWalklimit(), units->at(unitIndex)->getAttackrange(), true, units->at(unitIndex)->getTilePosition(), sf::Color::White);
	}
	playerB.setActive(!playerB.getActive());
	for (auto const & p : unitBContainer) {						// alle units van B deselecteren
		p->setSelected(false);
		p->resetTurn();
	}
	playerR.setActive(!playerR.getActive());
	for (auto const & p : unitRContainer) {						// alle units van R deselecteren
		p->setSelected(false);
		p->resetTurn();
	}
	inFactory = false;
}

void Game::spawnBomber(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Bomber(textureID::DRAGON, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

void Game::spawnUnit(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Unit(textureID::UNIT, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

void Game::spawnFactory(sf::Vector2f pos) {
	std::unique_ptr<Building> building(new Factory(textureID::FACTORY, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? buildingBContainer.push_back(std::move(building)) : buildingRContainer.push_back(std::move(building));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

void Game::spawnHQ(sf::Vector2f pos) {
	std::unique_ptr<Building> building(new Headquarters(textureID::HEADQUARTER, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? buildingBContainer.push_back(std::move(building)) : buildingRContainer.push_back(std::move(building));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

void Game::spawnResource(sf::Vector2f pos) {
	std::unique_ptr<Resource> resource(new Resource(textureID::RESOURCE, textures, V2fModulo(pos, TILESIZE)));
	resourceContainer.push_back(std::move(resource));
	for (auto const & t : terrainContainer) {
		if (t->checkClicked(pos)) {
			t->setFree(false);
		}
	}
}

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

sf::Vector2f Game::checkSpawn(sf::Vector2f pos) {
	for (auto const & t : terrainContainer) {
		if ((t->getColor() == sf::Color::Green) && checkSpaceFree(t->getTilePosition())) {
			return t->getTilePosition();
		}
	}
	return pos;
}

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

bool Game::checkSpaceFree(sf::Vector2f pos) {
	for (auto const & t : terrainContainer) {
		if ((t->checkClicked(pos)) && (!(t->getFree()))) {			// checken of dit terrain vakje wel vrij is
			return false;
		}
	}
	return true;
}

void Game::markField(int walklimit, int attackrange, bool clear, sf::Vector2f position, sf::Color color) {					// mark the field in order to show a units walking limit
	int index;
	for (auto const & t : terrainContainer) {
		if ((t->getTilePosition() == position)) {
			auto it = std::find(terrainContainer.begin(), terrainContainer.end(), t);
			if (it != terrainContainer.end()) {
				index = std::distance(terrainContainer.begin(), it);
			}
		}
	}
	if (clear) {
		markRange(attackrange, index, sf::Color::White);
	}
	else {
		markRange(attackrange, index, sf::Color::Magenta);
	}
	markRange(walklimit, index, color);
}

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
		}
	}
}

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

void Game::HUD() {
	text.setColor(getActivePlayer().getPlayer());								//stel de tekstkleur in op de kleur van de huidige speler
	text.setString("Money: " + std::to_string(getActivePlayer().getMoney()));   //schrijf hoeveel geld de speler heeft
	text.setPosition(510, 0);
	window.draw(text);
	text.setString("Health: " + std::to_string(getActivePlayer().getPoints()));	//schrijf hoeveel health de speler heeft
	text.setPosition(510, 40);
	window.draw(text);
	if (unitSelected)
	{
		std::vector<std::unique_ptr<Unit>> * units;
		if (allySelected)
		{
			units = &(playerB.getActive() ? unitBContainer : unitRContainer);
		}
		else
		{
			playerB.getActive() ? text.setColor(playerR.getPlayer()) : text.setColor(playerB.getPlayer());
			units = &(playerB.getActive() ? unitRContainer : unitBContainer);
		}
		//std::cout << "unitindex: " << unitIndex << "\n";
		text.setString("unit: ");
		text.setPosition(510, 80);
		window.draw(text);
		text.setString("HP:" + std::to_string(units->at(unitIndex)->getHP()));
		text.setPosition(510, 110);
		window.draw(text);
		text.setString("DP: " + std::to_string(units->at(unitIndex)->getDP()));
		text.setPosition(510, 140);
		window.draw(text);
	}
}

void Game::render() {
	window.clear();
	if (inMenu) {
		for (const auto & p : menuContainer) {
			p->draw(window);
		}
	}
	else {
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
		HUD();
	}
	window.display();
}