#include "PokemonPicker.hpp"

Pokemon* PokemonPicker::RandomPokemon(const vector<Pokemon*>& pokemonList, const unsigned int seed)
{
	//Passing the time of the system to the seed to generate a truly random number
	srand(time(0) + seed);
	int randomValue = rand() % pokemonList.size();
	return pokemonList[randomValue];
}