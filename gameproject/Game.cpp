//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"

Game::Game() :
	window(sf::VideoMode(640, 480), "SFML window"),
	playerB{ sf::Color::Blue, true},
	playerR{ sf::Color::Red, false}
{
	loadTextures();
	makePlayfield();
	music.play(musicID::MENUTHEME);
	music.setVolume(10);
}

void Game::loadTextures() {
	textures.load(textureID::GRASS, "grass.jpg");
	textures.load(textureID::ROAD, "road.jpg");
	textures.load(textureID::UNIT, "unit.jpg");
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

void Game::handleInput(sf::Keyboard::Key key, bool b) {
	if (key == sf::Keyboard::W) {
		sf::Vector2i pos = (sf::Mouse::getPosition(window));
		std::unique_ptr<Unit> unit(new Unit(textureID::UNIT, textures, V2f_from_V2i(v2i_MOD(pos, TILESIZE)), getActivePlayer().getPlayer()));
		if(playerB.getActive())	unitBContainer.push_back(std::move(unit));
		else unitRContainer.push_back(std::move(unit));
	}
	else if (key == sf::Keyboard::S) {
		switchPlayer();
		std::cout << "switch player";
		//KEYBOARD ALLEEN PRESS AFVANGEN NOG DOEN
	}
	/*
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
		//*/
}

void Game::handleMouse(sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		// hier wat er moet gebeuren bij linker muisklik:
		// - check position van muis

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (playerB.getActive()) {
				for (auto const & p : unitBContainer) {								// container is de container van jou
					p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)));
				}
			}
			else {
				for (auto const & p : unitRContainer) {								// container is de container van jou
					p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)));
				}
			}
			
		}

		// - check op deze position overeenkomt met object uit container (unit)
		// - doe actie die bij die unit hoort! (doorsturen naar de unit en die handelt het verder af)      (unit).mouseAction()
	}
	//doet momenteel de switchplayer voor rechtermuisklik
	if (button == sf::Mouse::Right) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			switchPlayer();
		}
	}
}

Player Game::getActivePlayer() {
	if (playerB.getActive()) {
		return playerB;
	}
	else return playerR;
}

void Game::switchPlayer() {
	playerB.setActive(!playerB.getActive());
	playerR.setActive(!playerR.getActive());
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handleInput(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				handleMouse(event.mouseButton.button);
				break;
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

void Game::update() {

}

void Game::render() {
	window.clear();
	for (const auto & p : terrainContainer) {
		p->draw(window);
	}
	for (const auto & p : unitBContainer) {
		p->draw(window);
	}
	for (const auto & p : unitRContainer) {
		p->draw(window);
	}
	window.display();
}