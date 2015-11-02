//File PlayerButton.h

#ifndef _PLAYERBUTTON_H
#define _PLAYERBUTTON_H

#include "Button.h"
#include "CommandQueue.h"

class PlayerButton : public Button {
public:
	PlayerButton(textureID, const textureHolder& textures, sf::Vector2f);

	virtual void handleClick(CommandQueue & queue);
};

class EndTurnButton : public PlayerButton {
public:
	EndTurnButton(textureID, const textureHolder& textures, sf::Vector2f);

	void handleClick(CommandQueue & queue) override;
};


#endif