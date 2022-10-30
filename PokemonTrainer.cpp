#include "PokemonTrainer.hpp"
//#include "ctime"

PokemonTrainer::PokemonTrainer(string identifier, string fileName, GameObject* parent)
	:SpriteObject(identifier, fileName, parent), poke(NULL) {}

void PokemonTrainer::RenderGameObject(sf::RenderWindow& window)
{
	SpriteObject::RenderGameObject(window);
	try {
		poke->RenderGameObject(window);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
}

void PokemonTrainer::SetRandomPokemon(Pokemon* pokemon)
{
	if (poke != NULL) poke->SetParent(NULL);
	poke = pokemon;
	poke->SetParent(this);
}

Pokemon* PokemonTrainer::GetPokemon(void)
{
	return this->poke;
}
