#include "Enemy.hpp"

Enemy::Enemy(string identifier, string fileName, PokemonTrainer* target, GameObject* parent)
	:PokemonTrainer(identifier, fileName, target, parent) {}//, TWO_SECONDS(120) 
//{
//	reactionTimer = TWO_SECONDS;
//}

void Enemy::DecideAction()
{
	if (!active) return;
	int randomChoice = rand() % 11; // range 0 - 10
	if (randomChoice >= 8) this->Heal(50);
	else if (randomChoice >= 3) this->Attack(*target);
	else this->Skip();
}