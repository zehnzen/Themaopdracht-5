//File TextureHolder.h

#ifndef _TEXTUREHOLDER_H
#define _TEXTUREHOLDER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Enums.h"

class TextureHolder {
public:
	//Laad het pad in van een soort texture dat we nodig hebben in een map. Pad hoeft maar 1x ingeladen te worden (bij meerdere keren breakt die)
	void load(textureID, const std::string & filename);

	//Geeft het pad van een bepaald id uit de map terug
	sf::Texture& find(textureID id);

private:
	//Map waar elke pad in opgeslagen wordt.
	std::map <textureID, std::unique_ptr<sf::Texture>> textureMap;
};

#endif
