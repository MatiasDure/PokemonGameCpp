#include "PokemonTrainer.hpp"
#include "ctime"

PokemonTrainer::PokemonTrainer(string identifier, sf::Vector2f startingPosition, string fileName, const vector<Pokemon*>& pokeList, const int seed, GameObject* parent)
	:SpriteObject(identifier, startingPosition, fileName, parent),
	poke(PokemonPicker::RandomPokemon(pokeList, seed)) 
{;
}

void PokemonTrainer::RenderGameObject(sf::RenderWindow& window)
{
	SpriteObject::RenderGameObject(window);
	poke.RenderGameObject(window);
}

Pokemon& PokemonTrainer::GetPokemon()
{
	return this->poke;
}
