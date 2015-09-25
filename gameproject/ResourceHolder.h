//file ResourceHolder.h

#ifndef _RESOURCEHOLDER_H
#define _RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <assert.h>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	//Laad het pad in van een soort texture dat we nodig hebben in een map. Pad hoeft maar 1x ingeladen te worden (bij meerdere keren breakt die)
	void load(Identifier id, const std::string & filename) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}
		auto tbAdded = resourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(tbAdded.second);
	}

	//Zelfde als hierboven maar dan met extra parameter voor sommige loadFromFile aanroepen
	template <typename Parameter>
	void load(Identifier id, const std::string & filename, Parameter para) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, para)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}
		auto tbAdded = resourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(tbAdded.second);
	}

	//Geeft het pad van een bepaald id uit de map terug
	Resource& get(Identifier id) {
		auto found = resourceMap.find(id);
		assert(found != resourceMap.end());

		return *found->second;
	}

	const Resource& get(Identifier id) const {
		auto found = resourceMap.find(id);
		assert(found != resourceMap.end());

		return *found->second;
	}

private:
	//Map waar elke pad in opgeslagen wordt.
	std::map <Identifier, std::unique_ptr<Resource>> resourceMap;
};


#endif