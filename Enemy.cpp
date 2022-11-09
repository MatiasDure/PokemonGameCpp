#include "Enemy.hpp"

Enemy::Enemy(string identifier, string fileName, PokemonTrainer* target, GameObject* parent)
	:PokemonTrainer(identifier, fileName, target, parent) {}

void Enemy::DecideAction()
{
	CheckActive(active);
	int randomChoice = rand() % 11; // range 0 - 10
	if (randomChoice >= 8) this->Heal(50);
	else if (randomChoice >= 3) this->Attack(*target);
	else this->Skip();
}