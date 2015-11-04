//File Sound.cpp

#include "Sound.h"

/**********************************************************************************************//**
 * @fn	Sound::Sound()
 *
 * @brief	Default constructor.
 **************************************************************************************************/

Sound::Sound() {
	soundFiles.load(soundID::WALKUNIT, "walk.wav");
}

/**********************************************************************************************//**
 * @fn	void Sound::play(soundID id)
 *
 * @brief	Plays the sound with the given identifier.
 *
 * @param	id	The identifier of the song.
 **************************************************************************************************/

void Sound::play(soundID id) {
	sounds.push_back(sf::Sound(soundFiles.get(id)));
	sounds.back().play();
}

/**********************************************************************************************//**
 * @fn	void Sound::removeStoppedSound()
 *
 * @brief	Removes the stopped sound.
 **************************************************************************************************/

void Sound::removeStoppedSound() {
	sounds.remove_if([](const sf::Sound & s) {
		return s.getStatus() == sf::Sound::Stopped;
	});
}

