//File Music.cpp

#include "Music.h"

Music::Music() :
	music(),
	musicFiles(),
	volume(100.f)
{
	musicFiles[musicID::MENUTHEME] = "themeMusic.ogg";
	musicFiles[musicID::MISSIONTHEME] = "missionMusic.ogg";
}

void Music::play(musicID id) {
	std::string filename = musicFiles[id];

	if (!music.openFromFile(filename)) throw std::runtime_error("Music " + filename + " could not be opened");

	music.setVolume(volume);
	music.setLoop(true);
	music.play();
}

void Music::stop() {
	music.stop();
}

void Music::setPaused(bool paused) {
	if (paused) {
		music.pause();
	}
	else music.play();
}

void Music::setVolume(float vol) {
	music.setVolume(vol);
}