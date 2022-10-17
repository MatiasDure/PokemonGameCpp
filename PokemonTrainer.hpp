#pragma once
#include "SpriteObject.hpp"
#include "Pokemon.hpp"
#include "PokemonPicker.hpp"

class PokemonTrainer : public SpriteObject
{
private:

protected:
//pokemon
	Pokemon poke;
public:
//constructor
	PokemonTrainer(string identifier, sf::Vector2f startingPosition, string fileName,const vector<Pokemon*>& pokeList, const int seed, GameObject* parent = NULL);
	void SpawnPokemon();
	void RenderGameObject(sf::RenderWindow& window) override;
	Pokemon& GetPokemon();
	static void UpdateInstance();
};