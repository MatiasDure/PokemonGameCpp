#pragma once
#include "PokemonTrainer.hpp"

class Enemy : public PokemonTrainer
{
private:
public:
	//constructor
	Enemy(string identifier, sf::Vector2f startingPositon, string fileName, const vector<Pokemon*>& pokeList, const int seed, GameObject* parent = NULL);
};
