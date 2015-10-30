// file ReadInput.h

#ifndef _READINPUT_H
#define _READINPUT_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "exceptions.h"

class ReadInput {
public:
	char read(std::ifstream & input);
private:
};

#endif