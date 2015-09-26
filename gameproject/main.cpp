//File main.cpp

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ResourceHolder.h"

int main() {
	ResourceHolder<sf::Texture, textureID> textures;
	//textures.load(textureID::GRASS, "grass.jpg");
	textures.load(textureID::GRASS, "tile.jpg");

	Game game(textures.get(textureID::GRASS));
	game.run();
	return 0;
}