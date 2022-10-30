#include "BattleControl.hpp"

BattleControl::BattleControl(string identifier, string fileName, GameObject* parent)
	: SpriteObject(identifier, fileName, parent),
	attack("attackButton","kirby.png",this),
	skip("attackButton", "kirby.png", this), 
	surrender("attackButton", "kirby.png", this){}