#include "BattleControl.hpp"

BattleControl::BattleControl(string identifier, sf::Vector2f startingPosition, string fileName, GameObject* parent)
	: SpriteObject(identifier, startingPosition, fileName, parent),
	attack("attackButton",sf::Vector2f(0,0),"kirby.png",this),
	skip("attackButton", sf::Vector2f(0, 0), "kirby.png", this), 
	surrender("attackButton", sf::Vector2f(0, 0), "kirby.png", this){}