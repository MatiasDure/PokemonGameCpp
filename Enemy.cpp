#include "Enemy.hpp"

Enemy::Enemy(string identifier, string fileName, PokemonTrainer* target, GameObject* parent)
	:PokemonTrainer(identifier, fileName, target, parent) {}

void Enemy::DecideAction()
{
	CheckActive(active);
	int randomChoice = rand() % 11; // range 0 - 10
	if (randomChoice >= 8)
	{
		printf("Enemy healed!\n");
		this->Heal(50);
	}
	else if (randomChoice >= 2)
	{
		printf("Enemy attacked!\n");
		this->Attack(*target);
	}
	else
	{
		printf("Enemy did nothing!\n");
		this->Skip();
	}
}