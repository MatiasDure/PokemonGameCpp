#include "FightManager.h"
#include "Pokemon.hpp"

FightManager::FightManager(Player& player, Enemy& enemy, string identifier, GameObject* parent) :
	GameObject(identifier, parent),
	player(player), enemy(enemy), score(0), seed(0), win(false), lose(false), TWO_SECONDS(120),
	turn("Turn"), playerHp("PlayerHP"), enemyHp("EnemyHP"), continueButton("Continue", "start.png")
{
	this->continueButton.SetPosition(600,400);
	this->continueButton.SetScale(0.6, 0.6);
	this->continueButton.SetActive(false);
	this->continueButton.SetBehavior([this]() {
		this->ResetGame(false);
		});

	this->InitializePokemonList();
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
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
	turn.SetPosition(460, 50);
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
	enemyTimer = TWO_SECONDS;
}

//Clearing the pokemons allocated in the heap
FightManager::~FightManager()
{
	std::vector<Pokemon*>::iterator pokemonIterator = pokemonList.begin();
	while (pokemonIterator != pokemonList.end())
	{
		delete* pokemonIterator;
		pokemonIterator++;
	}
}

void FightManager::DecideStartingPlayer()
{
	int decision = rand() % 2;
	if (decision) this->player.SwitchTurn();
	else this->enemy.SwitchTurn();
}

void FightManager::Update(sf::RenderWindow& window)
{

	CheckActive(active);
	
	//checking game status
	if (!(win || lose))
	{
		int currentEnemyHp = enemy.GetPokemon()->GetHP();
		int currentPlayerHp = player.GetPokemon()->GetHP();
		this->UpdateText(this->enemyHp, "Enemy's HP: " + to_string(currentEnemyHp));
		this->UpdateText(this->playerHp, "Player's HP: " + to_string(currentPlayerHp));
		this->CheckGameStatus(currentPlayerHp, currentEnemyHp);
	}
	else
	{
		if (win)
		{
			if (!increasedPoint)
			{
				score++;
				increasedPoint = true;
			}
			this->continueButton.SetActive(true);
			this->UpdateText(this->turn,"You Win!");
		}
		else
		{
			this->UpdateText(this->turn, "You Lose!");
			this->ResetGame(true);
		}
		return;
	}

	//player's turn
	if (this->player.GetTurn())
	{
		this->UpdateText(this->turn, "Player's Turn");
		return;
	}

	//Enemy's turn: simulating thinking time for enemy "AI"
	this->UpdateText(this->turn, "Enemy's Turn");
	if (enemyTimer <= 0)
	{
		this->enemy.DecideAction();
		this->SwitchTurns();
		enemyTimer = TWO_SECONDS;
	}
	else enemyTimer--;
}

void FightManager::RenderGameObject(sf::RenderWindow& window)
{
	GameObject::RenderGameObject(window);
	turn.RenderGameObject(window);
	playerHp.RenderGameObject(window);
	enemyHp.RenderGameObject(window);
	continueButton.RenderGameObject(window);
	continueButton.Update(window);
}

void FightManager::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	GameObject::HandleEvent(event, window);
	this->continueButton.HandleEvent(event, window);
}

bool FightManager::gameWon(void) const
{
	return this->win;
}

bool FightManager::gameLost(void) const
{
	return this->lose;
}

void FightManager::SwitchTurns()
{
	this->player.SwitchTurn();
	this->enemy.SwitchTurn();
}

void FightManager::ResetGame(bool backToMainMenu)
{
	//deactivating continue button
	this->continueButton.SetActive(false);

	//deciding new turn
	this->player.SetTurn(false);
	this->enemy.SetTurn(false);
	this->DecideStartingPlayer();

	//resetting game status
	this->win = false;
	this->lose = false;
	this->increasedPoint = false;
	this->enemyTimer = TWO_SECONDS;
	
	//resetting pokemons
	this->player.GetPokemon()->ResetPokemon();
	this->enemy.GetPokemon()->ResetPokemon();
	
	//selecting new random pokemon
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;

	if (backToMainMenu)
	{
		cout << score << "!!!!!!!!!!!!!" << endl;
		//Create function to compare the score gotten this turn with highscore, and update it if necessary


		score = 0;
	}
}

void FightManager::NextLevel()
{
}

void FightManager::UpdateText(TextObject& textObj, const string text)
{
	textObj.SetText(text);
}

void FightManager::SetHighScores()
{
}

void FightManager::ReadHighScores()
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

void FightManager::InitializePokemonList()
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

void FightManager::CheckGameStatus(const int playerLife, const int enemyLife)
{
	if (playerLife <= 0) lose = true;
	else if (enemyLife <= 0) win = true;
}
