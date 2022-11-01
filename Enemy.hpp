#pragma once
#include "PokemonTrainer.hpp"

class Enemy : public PokemonTrainer
{
private:
	//int reactionTimer;
	//const int TWO_SECONDS;
public:
	Enemy(string identifier, string fileName, PokemonTrainer* target = NULL, GameObject* parent = NULL);

	void DecideAction();
	//void AiUpdate();
};
