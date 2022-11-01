#include "GameManager.hpp"

GameManager::GameManager(Player& player, Enemy& enemy, string identifier, GameObject* parent) :
	GameObject(identifier, parent),
	player(player), enemy(enemy), score(0), seed(0), win(false), lose(false), enemyTimer(120),
	turn("Turn"), playerHp("PlayerHP"), enemyHp("EnemyHP")
{
	this->InitializePokemonList();
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList,seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList,seed));
	this->seed++;
	this->DecideStartingPlayer();
	turnText = player.GetTurn() ? "Player's Turn" : "Enemy's Turn";
	playerHpText = "Player's HP: " + to_string(player.GetPokemon()->GetHP());
	enemyHpText = "Enemy's HP: " + to_string(enemy.GetPokemon()->GetHP());
	cout << enemyHpText << endl;
	
	//setting text for game
	turn.SetText(turnText);
	turn.SetFont("font.ttf");
	turn.SetColor(sf::Color::White);
	turn.SetPosition(460,50);
	turn.SetSize(50);

	playerHp.SetText(playerHpText);
	playerHp.SetFont("font.ttf");
	playerHp.SetColor(sf::Color::Blue);
	playerHp.SetPosition(200, 550);
	playerHp.SetSize(50);

	enemyHp.SetText(enemyHpText);
	enemyHp.SetFont("font.ttf");
	enemyHp.SetColor(sf::Color::Red);
	enemyHp.SetPosition(700, 550);
	enemyHp.SetSize(50);
}

void GameManager::DecideStartingPlayer()
{
	//srand(time(0));
	int decision = rand() % 2;
	if (decision) this->player.SwitchTurn();
	else this->enemy.SwitchTurn();
}

void GameManager::Update(sf::RenderWindow& window)
{
	this->UpdateText(this->enemyHp, "Enemy's HP: " + to_string(enemy.GetPokemon()->GetHP()));
	this->UpdateText(this->playerHp, "Player's HP: " + to_string(player.GetPokemon()->GetHP()));
	
	if (this->player.GetTurn())
	{
		this->UpdateText(this->turn, "Player's Turn");
		return;
	}
	//simulate thinking time for enemy "AI"
	//Sleep(2000);
	this->UpdateText(this->turn, "Enemy's Turn");
	if (enemyTimer <= 0)
	{
		this->enemy.DecideAction();
		this->SwitchTurns();
		enemyTimer = 120;
	}
	else enemyTimer--;
}

void GameManager::RenderGameObject(sf::RenderWindow& window)
{
	window.draw(turn.GetTextObject());
	window.draw(playerHp.GetTextObject());
	window.draw(enemyHp.GetTextObject());
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

void GameManager::UpdateText(TextObject& textObj, string text)
{
	textObj.SetText(text);
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

