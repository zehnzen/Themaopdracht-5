//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);


Game::Game() :
	window(sf::VideoMode(640, 480), "SFML window"),
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

void Game::loadMenu()
{
	inMenu = true;
	//texture voor menu

	std::unique_ptr<MenuButton>background(new MenuButton(textureID::BACKGROUND, textures, sf::Vector2f(0, 0)));
	menuContainer.push_back(std::move(background));		//[0]

	std::unique_ptr<MenuButton> startButton(new MenuButton(textureID::START, textures, sf::Vector2f(50, 260)));
	menuContainer.push_back(std::move(startButton));	//[1]
	
	//muteButton en backButton buiten scherm laden. Deze worden later met setposition terug gehaald.
	std::unique_ptr<MenuButton> muteButton(new MenuButton(textureID::MUTE, textures, sf::Vector2f(50, 1000)));
	menuContainer.push_back(std::move(muteButton));		//[2]

	std::unique_ptr<MenuButton> exitButton(new MenuButton(textureID::EXIT, textures, sf::Vector2f(50, 400)));
	menuContainer.push_back(std::move(exitButton));		//[3]
	
	std::unique_ptr<MenuButton> optionButton(new MenuButton(textureID::OPTION, textures, sf::Vector2f(50, 330)));
	menuContainer.push_back(std::move(optionButton));	//[4]
	//muteButton en backButton buiten scherm laden. Deze worden later met setposition terug gehaald.
	std::unique_ptr<MenuButton> backButton(new MenuButton(textureID::BACK, textures, sf::Vector2f(50, 1000)));
	menuContainer.push_back(std::move(backButton));		//[5]

}

void Game::loadTextures() {
	textures.load(textureID::GRASS, "grass.jpg");
	textures.load(textureID::ROAD, "road.jpg");
	textures.load(textureID::UNIT, "unit.jpg");
	textures.load(textureID::DRAGON, "dragon.png");
	textures.load(textureID::BACKGROUND, "images//background.jpg");
	textures.load(textureID::START, "images//start.png");
	textures.load(textureID::OPTION, "images//option.png");
	textures.load(textureID::EXIT, "images//exit.png");
	textures.load(textureID::MUTE, "images//muteSound.png");
	textures.load(textureID::BACK, "images//back.png");
}

void Game::makePlayfield() {
	const int playfieldX = 10;
	const int playfieldY = 8;

	for (float y = 0; y < playfieldY; y++) {
		for (float x = 0; x < playfieldX; x++) {
			if (x == 3 || x == 6) {
				std::unique_ptr<Terrain> terrain(new Terrain(textureID::ROAD, textures, sf::Vector2f{ x * TILESIZE, y * TILESIZE }));
				terrainContainer.push_back(std::move(terrain));
			}
			else {
				std::unique_ptr<Terrain> terrain(new Terrain(textureID::GRASS, textures, sf::Vector2f{x * TILESIZE, y * TILESIZE}));
				terrainContainer.push_back(std::move(terrain));
			}
		}
	}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Game::handleKeypress(sf::Keyboard::Key key, bool b) {
	//Deze commands alleen bij indrukken
	if (!b) {
		if (key == sf::Keyboard::W) {
			spawnUnit(V2f_from_V2i(sf::Mouse::getPosition(window)));
		}
		else if (key == sf::Keyboard::A) {
			spawnBomber(V2f_from_V2i(sf::Mouse::getPosition(window)));
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
		if(inMenu)
		{
			for (auto const & p : menuContainer) {
				if (p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)), window, menuContainer, music) == 1) {//TODO test voor start
					inMenu = false;
				}
			}
		}
		else{
			markField(oldUnitWalklimit, oldUnitPosition, sf::Color::White);
			if (playerB.getActive()) {							// BLAUWE TEAM
				sf::Vector2f mPosition = V2f_from_V2i(sf::Mouse::getPosition(window));
				for (auto const & p : unitBContainer) {
					if (p->checkSelected(mPosition)) {
						oldUnitPosition = p->getTilePosition();		// onthouden voor het deselecteren van de tiles
						oldUnitWalklimit = p->getWalklimit();
						markField(oldUnitWalklimit, oldUnitPosition, sf::Color::Blue);
					}
					else {
						int i = 0;
						for (auto const & q : unitRContainer) {
							i++;
							if (q->checkClicked(V2f_from_V2i(sf::Mouse::getPosition(window)))) {	// check of vijand wordt aangeklikt en dus of er een aanval moet komen
								if (q->damage(p->attack())) {		// hij krijgt true mee als hij geen hp meer heeft, dus dan moet je hem verwijderen uit de container
									unitRContainer.erase(unitRContainer.begin() + i - 1);
									break;
								}
							}
						}
						p->walk(mPosition);
						p->setOldSelected(false);
					}
				}
			}
			else {												// RODE TEAM
				sf::Vector2f mPosition = V2f_from_V2i(sf::Mouse::getPosition(window));
				for (auto const & p : unitRContainer) {
					if (p->checkSelected(mPosition)) {
						oldUnitPosition = p->getPosition();		// onthouden voor het deselecteren van de tiles
						oldUnitWalklimit = p->getWalklimit();
						markField(oldUnitWalklimit, oldUnitPosition, sf::Color::Red);
					}
					else {
						int i = 0;
						for (auto const & q : unitBContainer) {
							i++;
							if (q->checkClicked(V2f_from_V2i(sf::Mouse::getPosition(window)))) {	// check of vijand wordt aangeklikt en dus of er een aanval moet komen
								if (q->damage(p->attack())) {		// hij krijgt true mee als hij geen hp meer heeft, dus dan moet je hem verwijderen uit de container
									unitBContainer.erase(unitBContainer.begin() + i - 1);
									break;
								}
							}
						}

						p->walk(mPosition);
						p->setOldSelected(false);
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

//---------------------------------------------------------------------------------------------------------------------------------

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
	if (playerB.getActive()) { unitBContainer.push_back(std::move(unit)); }
	else { unitRContainer.push_back(std::move(unit)); }
}

void Game::spawnUnit(sf::Vector2f pos) {
	std::unique_ptr<Unit> unit(new Unit(textureID::UNIT, textures, V2fModulo(pos, TILESIZE), getActivePlayer().getPlayer()));
	if (playerB.getActive()) { unitBContainer.push_back(std::move(unit)); }
	else { unitRContainer.push_back(std::move(unit)); }
}

void Game::markField(int walklimit, sf::Vector2f position, sf::Color color) {					// mark the field in order to show a units walking limit
	for (auto const & t : terrainContainer) {
		//if(t->getPosition() == position) {		// nog ff origin verplaatsen in de sprites!!! anders werkt het niet. origin in het midden. daarom eerst nog ff die hieronder:
		if((t->getPosition().x == position.x) && (t->getPosition().y == position.y)) {

			int index;

			auto it = std::find(terrainContainer.begin(), terrainContainer.end(), t);
			if (it != terrainContainer.end()) {
				index = std::distance(terrainContainer.begin(), it);
			}
			for (int i = 0; i <= walklimit; i++) {
				if((index - i) >= 0){						// checken of die terrain wel bestaat
					if ((index % 10) && ((index - i + 1)% 10)) {		// checken of de vakjes wel in dezelfde rij liggen
						terrainContainer.at(index - i)->changeColor(color);
					}
				}
				if ((index + i) <= 79) {											// 79 = playfieldX * playfieldY - 1 = 10 * 8 - 1
					if (((index + 1)% 10) && ((index + i) % 10)) {					// checken of de vakjes wel in dezelfde rij liggen
						terrainContainer.at(index + i)->changeColor(color);
					}
				}
				if ((index - (10 * i)) >= 0) {
					terrainContainer.at(index - (10 * i))->changeColor(color);		// 10 = playfieldX
				}
				if ((index + (10 * i)) <= 79) {			
					terrainContainer.at(index + (10 * i))->changeColor(color);		// 10 = playfieldX
				}
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
	//TODO implement Command message structure which will be iterated here and each command delivered to it's target where it'll handle it's implementation
	if (inMenu) {
		//TODO game doesn't update but handles menu
	}
	else {
		//TODO the game updates
		for (auto & p : unitBContainer) {
			p->update(dt);
		}
		for (auto & p : unitRContainer) {
			p->update(dt);
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
		for (const auto & p : terrainContainer) {
			p->draw(window);
		}
		for (const auto & p : unitBContainer) {
			p->draw(window);
		}
		for (const auto & p : unitRContainer) {
			p->draw(window);
		}

		HUD();
	}
	window.display();
}