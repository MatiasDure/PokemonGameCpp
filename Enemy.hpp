#pragma once
#include "PokemonTrainer.hpp"

class Enemy : public PokemonTrainer
{
private:
public:
	Enemy(string identifier, string fileName, PokemonTrainer* target = NULL, GameObject* parent = NULL);

	void DecideAction();
};
