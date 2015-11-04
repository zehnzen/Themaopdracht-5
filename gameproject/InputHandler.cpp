//File InputHandler.cpp

#include "InputHandler.h"
#include "V2Functions.h"

/**********************************************************************************************//**
 * @fn	InputHandler::InputHandler(sf::RenderWindow & window)
 *
 * @brief	Constructor.
 *
 * @param [in,out]	window	The window of the game.
 **************************************************************************************************/

InputHandler::InputHandler(sf::RenderWindow & window):
	window { window}
{}

/**********************************************************************************************//**
 * @fn	void InputHandler::processInput(CommandQueue & queue)
 *
 * @brief	Process the input described by queue.
 *
 * @param [in,out]	queue	The queue.
 **************************************************************************************************/

void InputHandler::processInput(CommandQueue & queue) {//QUEUE meegeven
	sf::Event event;
	while (window.pollEvent(event)) {
		Command command;
		command.pos = V2f_from_V2i(sf::Mouse::getPosition(window));
		switch (event.type) {
		case sf::Event::KeyPressed:
			handleKeypress(command, event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleKeypress(command, event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			handleMouseClick(command, event.mouseButton.button);
			break;
		case sf::Event::MouseMoved:
			command.id = commandID::ENTERED;
			break;
		case sf::Event::LostFocus:
			command.id = commandID::OPENMENU;
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			command.id = commandID::NONE;
		}
		queue.push(command);
	}
}

/**********************************************************************************************//**
 * @fn	void InputHandler::handleKeypress(Command & comm, sf::Keyboard::Key key, bool b)
 *
 * @brief	Handles the input in the keyboard.
 *
 * @param [in,out]	comm	The commands.
 * @param	key				The key that is being pressed/released.
 * @param	b				true means the key is being pressed, false is released.
 **************************************************************************************************/

void InputHandler::handleKeypress(Command & comm, sf::Keyboard::Key key, bool b) {
	if (!b) {
		if (key == sf::Keyboard::W) {
			comm.id = commandID::SPAWNUNIT;
		}
		else if (key == sf::Keyboard::A) {
			comm.id = commandID::SPAWNBOMBER;
		}
		else if (key == sf::Keyboard::F) {
			comm.id = commandID::SPAWNFACTORY;
		}
		else if (key == sf::Keyboard::H) {
			comm.id = commandID::SPAWNHQ;
		}
		else if (key == sf::Keyboard::R) {
			comm.id = commandID::SPAWNRESOURCE;
		}
		else if (key == sf::Keyboard::S) {
			comm.id = commandID::SWITCHPLAYER;
		}
		else if (key == sf::Keyboard::P) {
			comm.id = commandID::OPENMENU;
		}
	}
}

/**********************************************************************************************//**
 * @fn	void InputHandler::handleMouseClick(Command & comm, sf::Mouse::Button button)
 *
 * @brief	Handles the mouse clicks.
 *
 * @param [in,out]	comm	The commands.
 * @param	button			The mousebutton that is pressed.
 **************************************************************************************************/

void InputHandler::handleMouseClick(Command & comm, sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		comm.id = commandID::LEFTCLICK;
	}
	else if (button == sf::Mouse::Right) {
		comm.id = commandID::SWITCHPLAYER;
	}
}
