//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <array>
#include "V2Functions.h"
#include "Soldier.h"

Game::Game() :
	window(sf::VideoMode(640, 480), "SFML window"),
	playerB{ sf::Color::Blue, true},
	playerR{ sf::Color::Red, false}
	{
	initText();
	loadTextures();
	makePlayfield();
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
	for (auto const & p : unitBContainer) {						// alle units van B deselecteren
		p->setSelected(false);
	}
	playerR.setActive(!playerR.getActive());
	for (auto const & p : unitRContainer) {						// alle units van R deselecteren
		p->setSelected(false);
	}
}

/*void Game::markField() {									// mark the field (1 terrain) in order to show a units walking limit
	for (auto const & p : unitBContainer) {						// alle units van B deselecteren
		if (p->getSelected()) {
			for (auto const & t : terrainContainer) {
				t->changeColor(sf::Color::Yellow);
			}
			// terrain(textureID::ROAD, textures, sf::Vector2f{ x * TILESIZE, y * TILESIZE }));
		}
	}
} */

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

	window.display();
}