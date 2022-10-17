#pragma once
#include "PokemonTrainer.hpp"

class Player : public PokemonTrainer
{
private:
	//Menu object for player
	//Pokemon object for player

public:
	Player(string identifier, sf::Vector2f startingPosition, string fileName, const vector<Pokemon*>& pokemonList, const int seed, GameObject* parent = NULL);
};