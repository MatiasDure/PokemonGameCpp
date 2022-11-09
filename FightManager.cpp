#include "FightManager.h"
#include "Pokemon.hpp"
#include "GameManager.hpp"

FightManager::FightManager(Player& player, Enemy& enemy, string identifier, GameObject* parent) :
	GameObject(identifier, parent),
	player(player), enemy(enemy), score(0), seed(0), win(false), lose(false), TWO_SECONDS(120), lengthOfHighScores(4),
	turn("Turn"), playerHp("PlayerHP"), enemyHp("EnemyHP"), continueButton("Continue", "start.png")
{
	
	//Setting continue button
	this->continueButton.SetPosition(600,400);
	this->continueButton.SetScale(0.6, 0.6);
	this->continueButton.SetActive(false);
	this->continueButton.SetBehavior([this]() {
		this->ResetGame(false);
		});

	//Assigning pokemons to players
	this->InitializePokemonList();
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;

	//moving trainers and their pokes into position
	this->player.MoveObj(50, 300);
	this->enemy.MoveObj(1050, 10);
	this->MovePokesIntoPos();

	//assigning starting player
	this->DecideStartingPlayer();

	//setting text for game
	turnText = player.GetTurn() ? "Player's Turn" : "Enemy's Turn";
	playerHpText = "Player's HP: " + to_string(player.GetPokemon()->GetHP());
	enemyHpText = "Enemy's HP: " + to_string(enemy.GetPokemon()->GetHP());
	
	turn.SetText(turnText);
	turn.SetFont("font.ttf");
	turn.SetColor(sf::Color::White);
	turn.SetPosition(400, 50);
	turn.SetSize(50);

	playerHp.SetText(playerHpText);
	playerHp.SetFont("font2.ttf");
	playerHp.SetColor(sf::Color::Blue);
	playerHp.SetPosition(50, 100);
	playerHp.SetSize(40);

	enemyHp.SetText(enemyHpText);
	enemyHp.SetFont("font2.ttf");
	enemyHp.SetColor(sf::Color::Red);
	enemyHp.SetPosition(50, 50);
	enemyHp.SetSize(40);
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

void FightManager::MovePokesIntoPos()
{
	//moving pokes into position
	sf::Vector2f playerPos = this->player.GetPosition();
	this->player.GetPokemon()->SetPosition(playerPos.x + 400, playerPos.y + 260);
	sf::Vector2f enemyPos = this->enemy.GetPosition();
	this->enemy.GetPokemon()->SetPosition(-200 + enemyPos.x, 220 + enemyPos.y);
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

	this->MovePokesIntoPos();

	if (backToMainMenu)
	{
		cout << score << "!!!!!!!!!!!!!" << endl;
		//Create function to compare the score gotten this turn with highscore, and update it if necessary
		SetHighScores(CompareHighScores(score, lengthOfHighScores));
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

void FightManager::SetHighScores(int indexToPlace)
{
	for (int i = lengthOfHighScores; i > indexToPlace - 1; i--)
	{
		if(i != lengthOfHighScores) highscores[i + 1] = highscores[i];
		highscores[i] = score;
	}
}

int FightManager::CompareHighScores(int score, int index)
{
	if (index < 0) return 0;
	if (score > highscores[index]) CompareHighScores(score, index - 1);
	else return index - 1;
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
