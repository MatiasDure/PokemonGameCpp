#include "GameManager.hpp"

GameManager::GameManager(Player& player, Enemy& enemy, string identifier, GameObject* parent) :
	GameObject(identifier, parent),
	player(player), enemy(enemy), score(0), seed(0), win(false), lose(false), enemyTimer(120)
{
	this->InitializePokemonList();
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList,seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList,seed));
	this->seed++;
	this->DecideStartingPlayer();
}

void GameManager::DecideStartingPlayer()
{
	srand(time(0));
	int decision = rand() % 2;
	if (decision) this->player.SwitchTurn();
	else this->enemy.SwitchTurn();
}

void GameManager::Update(sf::RenderWindow& window)
{
	if (player.GetTurn()) return;
	//simulating thinking time
	//Sleep(2000);
	cout << "Enemy Thinking what to do" << endl;
	if (enemyTimer <= 0)
	{
		this->enemy.DecideAction();
		this->SwitchTurns();
		cout << "Enemy done with turn" << endl;
		enemyTimer = 120;
	}
	else enemyTimer--;
	//update the game screen
}

void GameManager::SwitchTurns()
{
	this->player.SwitchTurn();
	this->enemy.SwitchTurn();
}

void GameManager::ResetGame()
{
	this->score = 0;
	this->win = false;
	this->lose = false;
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;
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
		lineStream >> this->highscores[i++];
	}
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

