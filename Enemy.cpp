#include "Enemy.hpp"

Enemy::Enemy(string identifier, string fileName, PokemonTrainer* target, GameObject* parent)
	:PokemonTrainer(identifier, fileName, target, parent) {}

void Enemy::DecideAction()
{
	srand(time(0));
	int randomChoice = rand() % 11;
	if (randomChoice >= 8) this->Heal(50);
	else if (randomChoice >= 3) this->Attack(*target);
	else this->Skip();
}
