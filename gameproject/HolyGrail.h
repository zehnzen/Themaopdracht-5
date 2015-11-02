//File HolyGrail.h

#ifndef _HOLYGRAIL_H
#define _HOLYGRAIL_H

#include "GameObject.h"
#include "CommandQueue.h"

class HolyGrail : public GameObject {
public:
	HolyGrail(textureID, const textureHolder & textures, sf::Vector2f);

	void Reckoning(CommandQueue & queue, sf::Color);
};

#endif