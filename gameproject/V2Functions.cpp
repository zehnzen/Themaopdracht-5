//File V2Functions.cpp

#include <SFML/Graphics.hpp>
#include "V2Functions.h"

sf::Vector2f V2f_from_V2i(sf::Vector2i rhs) {
	return sf::Vector2f((float)rhs.x, (float)rhs.y);
}

sf::Vector2i v2i_MOD(sf::Vector2i & lhs, int rhs) {
	lhs.x = lhs.x - (lhs.x % rhs);
	lhs.y = lhs.y - (lhs.y % rhs);
	return lhs;
}

sf::Vector2i V2i_from_V2f(sf::Vector2f & rhs) {
	return sf::Vector2i((int)rhs.x, (int)rhs.y);
}

sf::Vector2f V2fModulo(sf::Vector2f & lhs, int rhs) {
	return V2f_from_V2i(v2i_MOD(V2i_from_V2f(lhs), rhs));
}