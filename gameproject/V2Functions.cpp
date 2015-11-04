//File V2Functions.cpp

#include <SFML/Graphics.hpp>
#include "V2Functions.h"

/**********************************************************************************************//**
 * @fn	sf::Vector2f V2f_from_V2i(sf::Vector2i rhs)
 *
 * @brief	Get V2f from V2i.
 *
 * @param	rhs	The right hand side (in this case the V2i).
 *
 * @return	A sf::Vector2f.
 **************************************************************************************************/

sf::Vector2f V2f_from_V2i(sf::Vector2i rhs) {
	return sf::Vector2f((float)rhs.x, (float)rhs.y);
}

/**********************************************************************************************//**
 * @fn	sf::Vector2i v2i_MOD(sf::Vector2i & lhs, int rhs)
 *
 * @brief	V2i modifier.
 *
 * @param [in,out]	lhs	The left hand side.
 * @param	rhs		   	The right hand side.
 *
 * @return	A sf::Vector2i.
 **************************************************************************************************/

sf::Vector2i v2i_MOD(sf::Vector2i & lhs, int rhs) {
	lhs.x = lhs.x - (lhs.x % rhs);
	lhs.y = lhs.y - (lhs.y % rhs);
	return lhs;
}

/**********************************************************************************************//**
 * @fn	sf::Vector2i V2i_from_V2f(sf::Vector2f & rhs)
 *
 * @brief	Get V2i from V2f.
 *
 * @param [in,out]	rhs	The right hand side (in this case a V2f).
 *
 * @return	A sf::Vector2i.
 **************************************************************************************************/

sf::Vector2i V2i_from_V2f(sf::Vector2f & rhs) {
	return sf::Vector2i((int)rhs.x, (int)rhs.y);
}

//Voor Vector2f haalt de resterende modulo af van het orginele getal.

/**********************************************************************************************//**
 * @fn	sf::Vector2f V2fModulo(sf::Vector2f & lhs, int rhs)
 *
 * @brief	V2f modulo.
 *
 * @param [in,out]	lhs	The left hand side.
 * @param	rhs		   	The right hand side.
 *
 * @return	A sf::Vector2f.
 **************************************************************************************************/

sf::Vector2f V2fModulo(sf::Vector2f & lhs, int rhs) {
	return V2f_from_V2i(v2i_MOD(V2i_from_V2f(lhs), rhs));
}

/**********************************************************************************************//**
 * @fn	sf::Vector2f operator+(sf::Vector2f & lhs, int rhs)
 *
 * @brief	Addition operator.
 *
 * @param [in,out]	lhs	The first value.
 * @param	rhs		   	A value to add to it.
 *
 * @return	The result of the addition.
 **************************************************************************************************/

sf::Vector2f operator+(sf::Vector2f & lhs, int rhs) {
	return sf::Vector2f(lhs.x + rhs, lhs.y + rhs);
}

/**********************************************************************************************//**
 * @fn	sf::Vector2f operator+=(sf::Vector2f & lhs, int & rhs)
 *
 * @brief	Addition assignment operator.
 *
 * @param [in,out]	lhs	The left hand side.
 * @param [in,out]	rhs	The right hand side.
 *
 * @return	The result of the operation.
 **************************************************************************************************/

sf::Vector2f operator+=(sf::Vector2f & lhs, int & rhs) {
	return sf::Vector2f(lhs.x + rhs, lhs.y + rhs);
}