//File Sound.h

#ifndef _SOUND_H
#define _SOUND_H

#include <SFML/Audio.hpp>
#include <list>
#include "Enums.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"

class Sound : sf::NonCopyable {
public:
	Sound();

	void play(soundID);
	void removeStoppedSound();

private:
	soundHolder soundFiles;
	std::list<sf::Sound> sounds;
};

#endif