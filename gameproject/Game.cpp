//File Game.cpp

#include <SFML\Graphics.hpp>
#include "Game.h"
#include "ResourceHolder.h"

Game::Game(sf::Texture & texList):
	window(sf::VideoMode(640,480), "SFML window")
{
	grass.setText(texList);
}

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
	grass.draw(window);
	window.display();
}