//File GameObject.cpp

#include "GameObject.h"

/**********************************************************************************************//**
 * @fn	GameObject::GameObject(textureID id, const textureHolder& textures, sf::Vector2f pos)
 *
 * @brief	Constructor.
 *
 * @param	id			The identifier of the GameObject.
 * @param	textures	The textures of the GameObject.
 * @param	pos			The position of the GameObject on the screen.
 **************************************************************************************************/

GameObject::GameObject(textureID id, const textureHolder& textures, sf::Vector2f pos):
	id{ id },
	sprite{ textures.get(id) }
{
	setPosition(pos);
}

/**********************************************************************************************//**
 * @fn	void GameObject::setTextRect(sf::IntRect rect)
 *
 * @brief	Sets text rectangle for the sprite.
 *
 * @param	rect	The rectangle of the sprite.
 **************************************************************************************************/

void GameObject::setTextRect(sf::IntRect rect) {
	sprite.setTextureRect(rect);
}

/**********************************************************************************************//**
 * @fn	void GameObject::setPosition(sf::Vector2f pos)
 *
 * @brief	Sets the position of the GameObject on the screen.
 *
 * @param	pos	The position on the screen.
 **************************************************************************************************/

void GameObject::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

/**********************************************************************************************//**
 * @fn	sf::Vector2f GameObject::getPosition()
 *
 * @brief	Gets the position of the GameObject.
 *
 * @return	The position on the screen.
 **************************************************************************************************/

sf::Vector2f GameObject::getPosition() {
	return sprite.getPosition();
}

/**********************************************************************************************//**
 * @fn	sf::Vector2f GameObject::getTilePosition()
 *
 * @brief	Gets tile position of the GameObject.
 *
 * @return	The tile position.
 **************************************************************************************************/

sf::Vector2f GameObject::getTilePosition() {
	sf::Vector2f value = sprite.getPosition();
	return V2fModulo(value, TILESIZE);
}

/**********************************************************************************************//**
 * @fn	void GameObject::update(sf::Time dt)
 *
 * @brief	Updates the sprite so an animation is possible.
 *
 * @param	dt	The delta time.
 **************************************************************************************************/

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

/**********************************************************************************************//**
 * @fn	void GameObject::draw(sf::RenderWindow & window)
 *
 * @brief	Draws the object sprite on the given window.
 *
 * @param [in,out]	window	The window of the game.
 **************************************************************************************************/

void GameObject::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

/**********************************************************************************************//**
 * @fn	void GameObject::handleMouse(sf::Vector2f pos)
 *
 * @brief	Handles the mouse events at a given position of the mouse.
 *
 * @param	pos	The position of the mouse.
 **************************************************************************************************/

void GameObject::handleMouse(sf::Vector2f pos) {

}