//File main.cpp

#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	bool exit = false;
	while (!exit) {
		Game game;
		game.run();
		exit = game.getExit();
	}
	return 0;
}