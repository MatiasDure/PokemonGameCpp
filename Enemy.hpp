#pragma once
#include "PokemonTrainer.hpp"

class Enemy : public PokemonTrainer
{
private:
public:
	//constructor
	Enemy(string identifier, string fileName, GameObject* parent = NULL);
};
