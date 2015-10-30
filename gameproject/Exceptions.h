// file exceptions.h

#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>

// END OF FILE
class endOfFile : public std::exception {
public:
	endOfFile() :
		s{ std::string{ "end of file" } }
	{}
	const char * what() const override {
		return s.c_str();
	}
private:
	std::string s;
};



// UNKNOWN SHAPES
class unknownCharacter : public std::exception {
public:
	unknownCharacter(const std::string & name) :
		s{ std::string{ "unknown character [" } +name + "]" }
	{}
	const char * what() const override {
		return s.c_str();
	}
private:
	std::string s;
};

#endif