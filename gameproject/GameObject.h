//File GameObject.h

#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "V2Functions.h"

class GameObject {
public:
	void draw(sf::RenderWindow & window);

	sf::Vector2f getPosition();
	sf::Vector2f getTilePosition();

	virtual void update(sf::Time);
	virtual void setPos(sf::Vector2f pos);
	virtual void handleMouse(sf::Vector2f pos);

protected:
	GameObject(textureID, const textureHolder& textures, sf::Vector2f pos);

	void setTextRect(sf::IntRect);

	textureID id;
	sf::Sprite sprite;
	std::size_t numFrames;
	std::size_t currentFrame = 0;
	sf::Vector2i frameSize = sf::Vector2i(TILESIZE, TILESIZE);
	sf::Time duration = sf::seconds(1);
	sf::Time elapsedTime = sf::Time::Zero;
	bool repeat;
};

#endif