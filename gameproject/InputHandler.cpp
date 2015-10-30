//File InputHandler.cpp

#include "InputHandler.h"
#include "V2Functions.h"

InputHandler::InputHandler(sf::RenderWindow & window):
	window { window}
{}

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
			handleMouse(command, event.mouseButton.button);
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

void InputHandler::handleMouse(Command & comm, sf::Mouse::Button button) {
	if (button == sf::Mouse::Left) {
		comm.id = commandID::LEFTCLICK;
	}
	else if (button == sf::Mouse::Right) {
		comm.id = commandID::RIGHTCLICK;
	}
}
