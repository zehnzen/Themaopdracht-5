//File Music.cpp

#include "Music.h"

/**********************************************************************************************//**
 * @fn	Music::Music()
 *
 * @brief	Default constructor.
 **************************************************************************************************/

Music::Music() :
	music{},
	musicFiles{},
	volume{10.f}
{
	musicFiles[musicID::MENUTHEME] = "themeMusic.ogg";
	musicFiles[musicID::MISSIONTHEME] = "missionMusic.ogg";
}

/**********************************************************************************************//**
 * @fn	void Music::play(musicID id)
 *
 * @brief	Plays the music with the given identifier.
 *
 * @exception	std::runtime_error	Thrown when a runtime error condition occurs.
 *
 * @param	id	The identifier of the song.
 **************************************************************************************************/

void Music::play(musicID id) {
	if (id != lastPlayed) {
		std::string filename = musicFiles[id];

		if (!music.openFromFile(filename)) throw std::runtime_error("Music " + filename + " could not be opened");

		music.setVolume(volume);
		music.setLoop(true);
		if (!paused) { music.play(); }
		
		lastPlayed = id;
	}
}

/**********************************************************************************************//**
 * @fn	void Music::stop()
 *
 * @brief	Stops the music from playing.
 **************************************************************************************************/

void Music::stop() {
	music.stop();
}

/**********************************************************************************************//**
 * @fn	void Music::setVolume(float vol)
 *
 * @brief	Sets a volume to a certain level.
 *
 * @param	vol	The volume of the music.
 **************************************************************************************************/

void Music::setVolume(float vol) {
	volume = vol;
	music.setVolume(volume);
}

/**********************************************************************************************//**
 * @fn	bool Music::getPaused()
 *
 * @brief	Gets wheither or not the music is paused.
 *
 * @return	true if music is paused, false if not.
 **************************************************************************************************/

bool Music::getPaused() {
	return paused;
}

/**********************************************************************************************//**
 * @fn	void Music::togglePlaying()
 *
 * @brief	Toggle between playing and pausing the music.
 **************************************************************************************************/

void Music::togglePlaying() {
	if (paused) { paused = false; music.play();}
	else { paused = true; music.pause(); }
}