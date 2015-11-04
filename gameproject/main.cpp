//File main.cpp

#include <SFML/Graphics.hpp>
#include "Game.h"

/**********************************************************************************************//**
 * @fn	int main()
 *
 * @brief	Main entry-point for this application.
 *
 * @return	Exit-code for the process - 0 for success, else an error code.
 **************************************************************************************************/

int main() {
	bool exit = false;
	while (!exit) {
		Game game;
		game.run();
		exit = game.getExit();
	}
	return 0;
}