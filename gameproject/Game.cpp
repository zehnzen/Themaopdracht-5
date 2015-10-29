//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :
	window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML window"),
	playerB{ sf::Color::Blue, true},
	playerR{ sf::Color::Red, false}
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
	std::unique_ptr<UnitButton> unitButton(new DragonButton(val10.id, textures, val10.pos));
	factoryButtons.push_back(std::move(unitButton));

	buttonVal val20{ textureID::ENDTURN, sf::Vector2f(50, 410) };
	std::unique_ptr<EndTurnButton> playerButton(new EndTurnButton(val20.id, textures, val20.pos));
	playerButtons.push_back(std::move(playerButton));
}

void Game::loadTextures() {
	textures.load(textureID::GRASS, "grass.jpg");
	textures.load(textureID::ROAD, "road.jpg");
	textures.load(textureID::UNIT, "unit.jpg");
	textures.load(textureID::DRAGON, "dragon.png");
	textures.load(textureID::FACTORY, "factory.jpg");
	textures.load(textureID::ENDTURN, "endTurn.png");
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

void Game::handleKeypress(sf::Keyboard::Key key, bool b) {
	//Deze commands alleen bij indrukken
	if (!b) {
		if (key == sf::Keyboard::W) {
			spawnUnit(V2f_from_V2i(sf::Mouse::getPosition(window)));
		}
		else if (key == sf::Keyboard::A) {
			spawnBomber(V2f_from_V2i(sf::Mouse::getPosition(window)));
		}
		else if (key == sf::Keyboard::F) {
			spawnFactory(V2f_from_V2i(sf::Mouse::getPosition(window)));
		}
		else if (key == sf::Keyboard::S) {
			switchPlayer();
		}
		else if (key == sf::Keyboard::P) {
			inMenu = true;
		}
	}
}

void Game::handleMouse(sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		sf::Vector2f mPosition = V2f_from_V2i(sf::Mouse::getPosition(window));

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
						sf::Vector2f location = currentPlayerBuildings->at(0)->getTilePosition();
						// kijken of hij wel daar mag worden gedropt
						//if(checkSpaceFree(std::vector<std::unique_ptr<Unit>> & container, sf::Vector2f pos)) {
						//for () {
						sf::Vector2f loc(location.x + TILESIZE, location.y + TILESIZE);
						//}
						if (checkSpaceFree(unitBContainer, loc)) {
							currentPlayerUnits->push_back(std::unique_ptr<Unit>(p->bAction(textures, loc, color)));
						}
						//location = location + 50;
						//currentPlayerUnits->push_back(std::unique_ptr<Unit>(p->bAction(textures, location, color)));
						inFactory = false;
					}
				}
			}
			else {
				unitControl(currentPlayerUnits, enemyPlayerUnits, color);
				for (const auto & p : *currentPlayerBuildings) {
					if (p->checkClicked(mPosition)) {
						inFactory = true;
					}
				}
			}
		}
	}
	//doet momenteel de switchplayer voor rechtermuisklik
	if (button == sf::Mouse::Right) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			switchPlayer();
		}
	}
}


void Game::unitControl(std::vector<std::unique_ptr<Unit>> * currentPlayerUnits, std::vector<std::unique_ptr<Unit>> * enemyPlayerUnits, sf::Color color) {			// het afhandelen van de movement, aanvallen en actions van de units
	sf::Vector2f mPosition = V2f_from_V2i(sf::Mouse::getPosition(window));
	if (!unitSelected) {
		markField(unitWalklimit, unitAttackrange, true, unitPosition, sf::Color::White);
		for (auto const & p : * currentPlayerUnits) {
			if (p->checkClicked(mPosition)) {
				unitSelected = true;
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
	}
	else if(unitSelected){
		// aanvallen:
		int i = 0;
		for (auto const & q : * enemyPlayerUnits) {
			i++;
			if (q->checkClicked(V2f_from_V2i(sf::Mouse::getPosition(window)))) {	// check of vijand wordt aangeklikt en dus of er een aanval moet komen
				if (checkAttack(mPosition)) {
					if (q->damage(currentPlayerUnits->at(unitIndex)->attack())) {		// hij krijgt true mee als hij geen hp meer heeft, dus dan moet je hem verwijderen uit de container
						enemyPlayerUnits->erase(enemyPlayerUnits->begin() + i - 1);
					}
				}
				break;
			}
		}
		if (checkWalk(mPosition)) {
			currentPlayerUnits->at(unitIndex)->walk(mPosition);		// lopen
		}
		currentPlayerUnits->at(unitIndex)->setSelected(false);
		unitSelected = false;
		markField(unitWalklimit, unitAttackrange, true, unitPosition, sf::Color::White);
	}
}

Player Game::getActivePlayer() {
	if (playerB.getActive()) {
		return playerB;
	}
	else { return playerR; }
}

void Game::switchPlayer() {
	playerB.setActive(!playerB.getActive());
	for (auto const & p : unitBContainer) {						// alle units van B deselecteren
		p->setSelected(false);
	}
	playerR.setActive(!playerR.getActive());
	for (auto const & p : unitRContainer) {						// alle units van R deselecteren
		p->setSelected(false);
	}
}

void Game::spawnBomber(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Bomber(textureID::DRAGON, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
}

void Game::spawnUnit(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Unit(textureID::UNIT, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? unitBContainer.push_back(std::move(unit)) : unitRContainer.push_back(std::move(unit));
}

void Game::spawnFactory(sf::Vector2f pos) {
	std::unique_ptr<Building> building(new Building(textureID::FACTORY, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	(playerB.getActive()) ? buildingBContainer.push_back(std::move(building)) : buildingRContainer.push_back(std::move(building));
}

bool Game::checkWalk(sf::Vector2f pos) {
	if(checkSpaceFree(unitBContainer, pos) && checkSpaceFree(unitRContainer, pos)) {
		for (auto const & t : terrainContainer) {
			if (t->checkClicked(pos)) {
				if ((t->getColor() == sf::Color::Blue) || (t->getColor() == sf::Color::Red)) {
					return true;
				}
			}
		}
	}
	return false;
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

bool Game::checkSpaceFree(std::vector<std::unique_ptr<Unit>> & container, sf::Vector2f pos) {
	for (auto const & t : container) {
		if (t->checkClicked(pos)) {			// checken of er geen andere unit op deze plek zit
			return false;
		}
	}
	return true;
}

void Game::markField(int walklimit, int attackrange, bool clear, sf::Vector2f position, sf::Color color) {					// mark the field in order to show a units walking limit
	int index;
	for (auto const & t : terrainContainer) {
		//if(t->getPosition() == position) {		// nog ff origin verplaatsen in de sprites!!! anders werkt het niet. origin in het midden. daarom eerst nog ff die hieronder:
		if ((t->getPosition().x == position.x) && (t->getPosition().y == position.y)) {

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

void Game::markRange(int limit, int index, sf::Color color) {
	limit--;
	if (index >= 0 && index <= ((playfieldX * playfieldY) - 1)) {						// checken of die terrain wel bestaat			// LINKS checken
		terrainContainer.at(index)->changeColor(color);
		if (limit > 0) {
			if (index % playfieldX) {
				markRange(limit, index - 1, color);
			}										// RECHTS checken
			if ((index + 1) % playfieldX) {				// checken of de vakjes wel in dezelfde rij liggen
				markRange(limit, index + 1, color);
			}
			if ((index - playfieldX) >= 0) {														// BOVEN checken
				markRange(limit, index - playfieldX, color);
			}
			if ((index + playfieldX) <= ((playfieldX * playfieldY) - 1)) {							// ONDER hem checken
				markRange(limit, index + playfieldX, color);
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
			processInput();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				handleKeypress(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handleKeypress(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				handleMouse(event.mouseButton.button);
				break;
			case sf::Event::LostFocus:
				inMenu = true;
				break;
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

void Game::update(sf::Time dt) {
	if (inMenu) {
		for (auto & p : menuContainer) {
			if (p->LoadedInScreen) {
				p->update(dt);
			}
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
		if (inFactory) {
			for (auto & p : factoryButtons) {
				p->update(dt);
			}
		}
	}
}

void Game::HUD() {
	text.setColor(getActivePlayer().getPlayer());
	text.setString("Money: " + std::to_string(getActivePlayer().getMoney()));
	text.setPosition(510, 0);
	window.draw(text);
	text.setString("Health: " + std::to_string(getActivePlayer().getPoints()));
	text.setPosition(510, 40);
	// Draw it
	window.draw(text);

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
		if (inFactory) {
			for (auto & p : factoryButtons) {
				p->draw(window);
			}
		}
		HUD();
	}
	window.display();
}