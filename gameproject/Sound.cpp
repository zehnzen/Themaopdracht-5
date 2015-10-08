//File Sound.cpp

#include "Sound.h"

Sound::Sound() {
	soundFiles.load(soundID::WALKUNIT, "walk.wav");
}

void Sound::play(soundID id) {
	sounds.push_back(sf::Sound(soundFiles.get(id)));
	sounds.back().play();
}

void Sound::removeStoppedSound() {
	sounds.remove_if([](const sf::Sound & s) {
		return s.getStatus() == sf::Sound::Stopped;
	});
}

