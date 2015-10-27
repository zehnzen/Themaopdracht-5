//File Entity.cpp

#include "Entity.h"

Entity::Entity(textureID id, const textureHolder& textures):
	id{ id },
	sprite{ textures.get(id), sf::IntRect(0, 0, TILESIZE, TILESIZE) }
{}

void Entity::setTextRect(sf::IntRect rect) {
	sprite.setTextureRect(rect);
}

void Entity::update(sf::Time dt) {

}

void Entity::setPos(sf::Vector2f pos) {
	sprite.setPosition(pos.x, pos.y);
}

sf::Vector2f Entity::getPos() {
	return sprite.getPosition();
}

void Entity::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

void Entity::handleMouse(sf::Vector2f pos) {

}