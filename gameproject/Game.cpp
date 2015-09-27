//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "ResourceHolder.h"
#include <array>
#include "v2f_from_v2i.h"

Game::Game():
	window(sf::VideoMode(640,480), "SFML window")
{
	loadTextures();
	makePlayfield();
}

void Game::loadTextures() {
	textures.load(textureID::GRASS, "grass.jpg");
	grass.setTexture(textures.get(textureID::GRASS));
	textures.load(textureID::UNIT, "unit.jpg");
	unit.setTexture(textures.get(textureID::UNIT));
}


// playfield aanmaken: (array van arrays) deze heeft de posities van alle plekken van het veld dus die kan je makkelijk geven aan je units enzo op deze manier-------
const int playfieldX = 10;	// zo kunnen ze bij het tekenen makkelijk worden meegegeven
const int playfieldY = 5;
static sf::Vector2f playfield[playfieldY][playfieldX];

void Game::makePlayfield() {
	float tileSize = 40;
	for (int y = 0; y < playfieldY; y++) {
		for (int x = 0; x < playfieldX; x++) {
			playfield[y][x] = sf::Vector2f{ x * tileSize,y *tileSize };
		}
	}
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Game::handleInput(sf::Keyboard::Key key, bool b) {
	/*if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
		*/
}
void Game::handleMouse(sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		// hier wat er moet gebeuren bij linker muisklik:
		// - check position van muis

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			for (auto const & p : container) {								// container is de container van jou
				p->handleMouse(V2f_from_V2i(sf::Mouse::getPosition(window)));
			}
		}

		// - check op deze position overeenkomt met object uit container (unit)
		// - doe actie die bij die unit hoort! (doorsturen naar de unit en die handelt het verder af)      (unit).mouseAction()
	}
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
				handleMouse(sf::Mouse::Button, sf::Mouse::getPosition());
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

	// op elke plek in het playfield gras tekenen:------------------------
	for (int y = 0; y < playfieldY; y++) {
		for (int x = 0; x < playfieldX; x++) {
			grass.draw(window, playfield[y][x]);
		}
	}
	// -------------------------------------------------------------------
	//grass.draw(window);
	window.display();
}