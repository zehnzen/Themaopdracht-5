//File main.cpp

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ResourceHolder.h"

int main() {
<<<<<<< HEAD
	ResourceHolder<sf::Texture, textureID> textures;
	//textures.load(textureID::GRASS, "grass.jpg");
	textures.load(textureID::GRASS, "grass.jpg");

	Game game(textures.get(textureID::GRASS));
=======
	Game game;
>>>>>>> master
	game.run();
	return 0;
}