//File Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"

class Entity {
public:
	void draw(sf::RenderWindow & window);

protected:
	Entity(textureID, const textureHolder& textures);
	sf::Vector2f getPos();

	void setTextRect(sf::IntRect);
	virtual void update(sf::Time);
	virtual void setPos(sf::Vector2f pos);
	virtual void handleMouse(sf::Vector2f pos);

	textureID id;
	sf::Sprite sprite;
	sf::Vector2i frameSize;
	std::size_t numFrames;
	std::size_t currentFrame;
	sf::Time duration;
	sf::Time elapsedTime;
	bool repeat;
};

#endif