// file ReadInput.cpp

#include <SFML/Graphics.hpp>
#include "ReadInput.h"


char ReadInput::read(std::ifstream & input) {
	std::string s;

	input >> s;

	if (s == "#") {
		return '1';
	}
	else if (s == "R") {
		return '2';
	}
	else if (s == "Ub") {
		return '3';
	}
	else if (s == "Db") {
		return '4';
	}
	else if (s == "Fb") {
		return '5';
	}
	else if (s == "Hb") {
		return '6';
	}
	else if (s == "Ur") {
		return '7';
	}
	else if (s == "Dr") {
		return '8';
	}
	else if (s == "Fr") {
		return '9';
	}
	else if (s == "Hr") {
		return '0';
	}
	else if (s == "") {
		throw endOfFile();
	}
	
	// DIT MOET TOCH GVD IN EEN SWITCH KUNNEN ?!!!!!!!!!!!!
	//switch (s) {
	//	case "#": return 1; break;
	//}
	throw unknownCharacter(s);
}