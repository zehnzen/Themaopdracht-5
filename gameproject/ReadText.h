// file ReadText.h

#ifndef _READTEXT_H
#define _READTEXT_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "exceptions.h"

class ReadText {
public:
	char read(std::ifstream & input);
private:
};

#endif