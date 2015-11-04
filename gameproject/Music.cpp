//File Music.cpp

#include "Music.h"

Music::Music() :
	music{},
	musicFiles{},
	volume{10.f}
{
	musicFiles[musicID::MENUTHEME] = "themeMusic.ogg";
	musicFiles[musicID::MISSIONTHEME] = "missionMusic.ogg";
}

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

void Music::stop() {
	music.stop();
}

void Music::setVolume(float vol) {
	volume = vol;
	music.setVolume(volume);
}

bool Music::getPaused() {
	return paused;
}

void Music::togglePlaying() {
	if (paused) { paused = false; music.play();}
	else { paused = true; music.pause(); }
}