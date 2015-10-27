//File GameObject.cpp

#include "GameObject.h"

GameObject::GameObject(textureID id, const textureHolder& textures, sf::Vector2f pos):
	id{ id },
	sprite{ textures.get(id), sf::IntRect(0, 0, TILESIZE, TILESIZE) }
{
	sprite.setPosition(pos);
}

void GameObject::setTextRect(sf::IntRect rect) {
	sprite.setTextureRect(rect);
}

void GameObject::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos.x, pos.y);
}

sf::Vector2f GameObject::getPosition() {
	return sprite.getPosition();
}

sf::Vector2f GameObject::getTilePosition() {
	sf::Vector2f value = sprite.getPosition();
	return V2fModulo(value, TILESIZE);
}

void GameObject::update(sf::Time dt) {
	sf::Time timePerFrame = duration / (float)numFrames;
	elapsedTime += dt;

	sf::Vector2i textureBounds(sprite.getTexture()->getSize());
	sf::IntRect textureRect = sprite.getTextureRect();

	if (currentFrame == 0) {
		textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
	}

	while (elapsedTime >= timePerFrame && (currentFrame <= numFrames || repeat))
	{
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}
		elapsedTime -= timePerFrame;
		if (repeat) {
			currentFrame = (currentFrame + 1) % numFrames;
			if (currentFrame == 0)
				textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
		}
		else
		{
			currentFrame++;
		}
	}
	sprite.setTextureRect(textureRect);
}

void GameObject::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void GameObject::handleMouse(sf::Vector2f pos) {

}