// file ReadInput.cpp

#include <SFML/Graphics.hpp>
#include "ReadText.h"

/**********************************************************************************************//**
 * @fn	char ReadInput::read(std::ifstream & input)
 *
 * @brief	Reads the given input.
 *
 * @exception	endOfFile			Thrown when an end of file error condition occurs.
 * @exception	unknownCharacter	Thrown when an unknown character error condition occurs.
 *
 * @param [in,out]	input	The input to read.
 *
 * @return	A char.
 **************************************************************************************************/

char ReadText::read(std::ifstream & input) {
	std::string s;

	input >> s;

	if (s == "#") {
		return '1';
	}
	else if (s == "R") {
		return '2';
	}
	else if (s == "G") {
		return '3';
	}
	//---------------------------------------------------------
	else if (s == "Ub") {
		return 'a';
	}
	else if (s == "Db") {
		return 'b';
	}
	else if (s == "Sb") {
		return 'c';
	}
	else if (s == "Fb") {
		return 'd';
	}
	else if (s == "Hb") {
		return 'e';
	}
	//----------------------------------------------------------
	else if (s == "Ur") {
		return 'z';
	}
	else if (s == "Dr") {
		return 'y';
	}
	else if (s == "Sr") {
		return 'x';
	}
	else if (s == "Fr") {
		return 'w';
	}
	else if (s == "Hr") {
		return 'v';
	}
	else if (s == "") {
		throw endOfFile();
	}

	throw unknownCharacter(s);
}