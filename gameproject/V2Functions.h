// file V2Functions

#ifndef _V2FUNCTIONS_H
#define _V2FUNCTIONS_H

#include <SFML/Graphics.hpp>

sf::Vector2f V2f_from_V2i(sf::Vector2i rhs);
sf::Vector2i v2i_MOD(sf::Vector2i & lhs, int rhs);
sf::Vector2i V2i_from_V2f(sf::Vector2f & rhs);

#endif