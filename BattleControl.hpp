#pragma once
#include "Button.hpp"

class BattleControl : public SpriteObject
{
private:
	Button attack, skip, surrender;
public:
	BattleControl(string identifier, sf::Vector2f startingPosition, string fileName, GameObject* parent = NULL);
};