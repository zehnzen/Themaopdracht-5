// file v2f_from_v2i.h

#include <SFML/Graphics.hpp>

sf::Vector2f V2f_from_V2i(sf::Vector2i rhs) {
	return sf::Vector2f((float)rhs.x, (float)rhs.y);
}