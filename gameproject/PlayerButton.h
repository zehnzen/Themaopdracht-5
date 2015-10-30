//File PlayerButton.h

#ifndef _PLAYERBUTTON_H
#define _PLAYERBUTTON_H

#include "Button.h"

class PlayerButton : public Button {
public:
	PlayerButton(textureID, const textureHolder& textures, sf::Vector2f);

	virtual buttonID handleClick();
};

class EndTurnButton : public PlayerButton {
public:
	EndTurnButton(textureID, const textureHolder& textures, sf::Vector2f);

	buttonID handleClick() override;
};


#endif