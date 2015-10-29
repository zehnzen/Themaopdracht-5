//File MenuButton

#ifndef _MENUBUTTON_H
#define _MENUBUTTON_H

#include "Button.h"
#include <array>

class MenuButton : public Button {
public:
	MenuButton(textureID, const textureHolder& textures);
	MenuButton(textureID, const textureHolder& textures, sf::Vector2f pos, sf::Vector2f direction);
	//TODO geeft nu int terug voor testing, moet later met commands gaan werken.
	void setPosition(sf::Vector2f) override;
	sf::Vector2f getPosition() override;
	void update(float t);
	void changeDirection(sf::Vector2f cD);
	void draw(sf::RenderWindow & window) override;	// draw methode met position erbij	
	int handleMouse(sf::Vector2f pos, sf::RenderWindow & window, std::vector<std::unique_ptr<MenuButton>> & container, Music & music);
	bool LoadedInScreen = false;

private:
	const sf::Vector2f outOfScreen = sf::Vector2f(-200, 800);
	sf::Vector2f position;
	sf::Vector2f direction;
	textureID id;
	sf::Sprite button;
	bool musicMuted = false;

	const sf::Vector2f vertical = sf::Vector2f(0, 1);
	const sf::Vector2f horizontal = sf::Vector2f(1, 0);

	const sf::Vector2f MenuPos1 = sf::Vector2f(800, 260);
	const sf::Vector2f MenuPos2 = sf::Vector2f(1000, 330);
	const sf::Vector2f MenuPos3 = sf::Vector2f(1200, 400);

	std::vector<sf::Vector2f> menuPosition = {
		{ sf::Vector2f(0, 0) },
		{ sf::Vector2f(800, 260) },
		{ sf::Vector2f(1000, 330) },
		{ sf::Vector2f(1200, 400) },
		{ sf::Vector2f(1000, 330) },
		{ sf::Vector2f(1200, 400) },
	};
	std::vector<sf::Vector2f>::iterator it;  // declare an iterator to a vector of strings
	int i;
};

#endif
