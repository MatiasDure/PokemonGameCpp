#pragma once
#include "SpriteObject.hpp"
#include "Pokemon.hpp"
#include "PokemonPicker.hpp"

class PokemonTrainer : public SpriteObject
{
private:

protected:
//pokemon
	Pokemon* poke;
public:
//constructor
	PokemonTrainer(string identifier, string fileName, GameObject* parent = NULL);
	void SpawnPokemon();
	void RenderGameObject(sf::RenderWindow& window) override;
	void SetRandomPokemon(Pokemon* pokemon);
	Pokemon* GetPokemon(void);
};