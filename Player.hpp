#pragma once
#include "PokemonTrainer.hpp"

class Player : public PokemonTrainer
{
private:

public:
	Player(string identifier, string fileName, GameObject* parent = NULL);
};