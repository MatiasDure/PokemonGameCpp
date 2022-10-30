#include "GameManager.hpp"

GameManager::GameManager(Player& player, Enemy& enemy, string identifier, GameObject* parent) : 
	GameObject(identifier, parent), 
	player(player), enemy(enemy), score(0), seed(0), win(false), lose(false)
{
	InitializePokemonList();
	player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList,seed));
	seed++;
	enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList,seed));
	seed++;
}

void GameManager::ResetGame()
{
	score = 0;
	win = false;
	lose = false;
	player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	seed++;
	enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	seed++;
}

void GameManager::NextLevel()
{
}

void GameManager::SetHighScores()
{
}

void GameManager::ReadHighScores()
{
	string line;
	ifstream myFile("highscores.txt");
	int i = 0;
	while (getline(myFile, line) && i < 5)
	{
		stringstream lineStream(line);
		lineStream >> highscores[i++];
	}
}

void GameManager::Update()
{
}

void GameManager::InitializePokemonList()
{
	string line;
	ifstream myFile("pokemons.txt");
	while (getline(myFile, line))
	{
		string name;
		int power, hp, stamina;

		//Creating a stream from the current line in the file
		stringstream lineStream(line);

		//pushing the values to the variables respectively
		lineStream >> name >> power >> hp >> stamina;

		//allocating memory in heap for each pokemon
		this->pokemonList.push_back(new Pokemon(name, power, hp, stamina, name, name + ".png"));
	}
	myFile.close();
}
