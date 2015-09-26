//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "ResourceHolder.h"

Game::Game(sf::Texture & texList):
	window(sf::VideoMode(640,480), "SFML window")
{
	grass.setText(texList);
}

// playfield aanmaken: (array van arrays) deze heeft de posities van alle plekken van het veld dus die kan je makkelijk geven aan je units enzo op deze manier-------
int playfieldX = 4;	// zo kunnen ze bij het tekenen makkelijk worden meegegeven
int playfieldY = 3;
sf::Vector2f playfield[3][4] = {
	{ sf::Vector2f{ 0,0 },		sf::Vector2f{ 50,0 },		sf::Vector2f{ 100,0 },		sf::Vector2f{ 150,0 } } ,
	{ sf::Vector2f{ 0,50 },		sf::Vector2f{ 50,50 },		sf::Vector2f{ 100,50 },		sf::Vector2f{ 150,50 } } ,
	{ sf::Vector2f{ 0,100 },	sf::Vector2f{ 50,100 },		sf::Vector2f{ 100,100 },	sf::Vector2f{ 150,100 } }
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
	for (int x = 0; x < playfieldX; x++) {
		for (int y = 0; y < playfieldY; y++) {
			grass.draw(window, playfield[y][x]);
		}
	}
	// -------------------------------------------------------------------
	//grass.draw(window);
	window.display();
}