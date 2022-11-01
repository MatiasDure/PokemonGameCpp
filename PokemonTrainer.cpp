#include "PokemonTrainer.hpp"
//#include "ctime"

PokemonTrainer::PokemonTrainer(string identifier, string fileName, PokemonTrainer* target, GameObject* parent)
	:SpriteObject(identifier, fileName, parent), target(target), poke(NULL), turn(false) {}

void PokemonTrainer::RenderGameObject(sf::RenderWindow& window)
{
	SpriteObject::RenderGameObject(window);
	if(poke != NULL) poke->RenderGameObject(window);
}

void PokemonTrainer::SetRandomPokemon(Pokemon* pokemon)
{
	if (poke != NULL) poke->SetParent(NULL);
	poke = pokemon;
	poke->SetParent(this);
}

void PokemonTrainer::SetTarget(PokemonTrainer* target)
{
	this->target = target;
}

void PokemonTrainer::SwitchTurn()
{
	turn = !turn;
}

void PokemonTrainer::TakeDamage(const int damage)
{
	poke->TakeDamage(damage);
}

void PokemonTrainer::Attack(PokemonTrainer& otherTrainer)
{
	//srand(time(0));
	int randomNum = rand() % 80 - 40; //num between -40 and 79 
	//cout << "damage to other: " + to_string(poke->GetPower() + randomNum) << endl;
	otherTrainer.TakeDamage(poke->GetPower() + randomNum);
}

void PokemonTrainer::Heal(const int amount)
{
	int currentHp = poke->GetHP();
	int originalHp = poke->GetOriginalHp();
	int sum = currentHp + amount;
	poke->TakeDamage(sum > originalHp ? currentHp - originalHp : -amount);
}

Pokemon* PokemonTrainer::GetPokemon(void)
{
	return this->poke;
}

bool PokemonTrainer::GetTurn(void)
{
	return turn;
}

PokemonTrainer* PokemonTrainer::GetTarget()
{
	return this->target;
}
