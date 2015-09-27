//File TextureHolder.cpp

#include "TextureHolder.h"
#include <assert.h>

void TextureHolder::load(textureID id, const std::string & filename) {
	std::unique_ptr<sf::Texture> resource(new sf::Texture());
	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}
	auto tbAdded = textureMap.insert(std::make_pair(id, std::move(resource)));
	assert(tbAdded.second);
}

//Geeft het pad van een bepaald id uit de map terug
sf::Texture& TextureHolder::find(textureID id) {
	auto found = textureMap.find(id);
	assert(found != textureMap.end());

	return *found->second;
}