//File Music.h

#ifndef _MUSIC_H
#define _MUSIC_H

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Enums.h"

class Music : private sf::NonCopyable {
public:
	Music();

	void play(musicID id);
	void stop();

	void setPaused(bool paused);
	void setVolume(float volume);

private:
	sf::Music music;
	std::map<musicID, std::string> musicFiles;
	float volume;
};

#endif