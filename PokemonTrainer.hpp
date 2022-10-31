#pragma once
#include "SpriteObject.hpp"
#include "Pokemon.hpp"
#include "PokemonPicker.hpp"

class PokemonTrainer : public SpriteObject
{
private:
protected:
	bool turn;
	PokemonTrainer* target;
//pokemon
	Pokemon* poke;
public:
//constructor
	PokemonTrainer(string identifier, string fileName, PokemonTrainer* target = NULL, GameObject* parent = NULL);
	//void SpawnPokemon();
	void RenderGameObject(sf::RenderWindow& window) override;
	void SetRandomPokemon(Pokemon* pokemon);
	void SetTarget(PokemonTrainer* target);
	void SwitchTurn();
	
	//Still needs implementation!!!
	void TakeDamage(const int damage);
	virtual void Attack(PokemonTrainer& otherTrainer);
	virtual void Heal(const int amount);
	virtual void Skip() {};
	//-----------------------------

	//Getters
	Pokemon* GetPokemon(void);
	bool GetTurn(void);
	PokemonTrainer* GetTarget();
};