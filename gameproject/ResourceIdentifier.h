//File ResourceIdentifier.h

#ifndef _RESOURCEIDENTIFIER_H
#define _RESOURCEIDENTIFIER_H

#include <SFML/Graphics.hpp>
#include "Enums.h"


template <typename Resource, typename Identifier> class ResourceHolder;
typedef ResourceHolder<sf::Texture, textureID> textureHolder;

#endif