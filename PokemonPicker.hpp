#pragma once
#include "Pokemon.hpp"
class PokemonPicker
{
private:
	static unsigned int amountCalled;
public:
	static Pokemon& RandomPokemon(const vector<Pokemon*>& pokemonList, const unsigned int seed);
};