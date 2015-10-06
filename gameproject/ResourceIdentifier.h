//File ResourceIdentifier.h

#ifndef _RESOURCEIDENTIFIER_H
#define _RESOURCEIDENTIFIER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enums.h"


template <typename Resource, typename Identifier> class ResourceHolder;
typedef ResourceHolder<sf::Texture, textureID> textureHolder;
typedef ResourceHolder<sf::SoundBuffer, soundID> soundHolder;

#endif