//File InputHandler.h

#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include "CommandQueue.h"

class InputHandler {
public:
	InputHandler(sf::RenderWindow & window);

	void processInput(CommandQueue & queue); //Queue meegeven by reference

private:
	void handleKeypress(Command & comm, sf::Keyboard::Key, bool);
	void handleMouse(Command & comm, sf::Mouse::Button);
	
	sf::RenderWindow & window;
};

#endif