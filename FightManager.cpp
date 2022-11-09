#include "FightManager.h"
#include "Pokemon.hpp"
#include "GameManager.hpp"

FightManager::FightManager(Player& player, Enemy& enemy, string identifier, GameObject* parent) :
	GameObject(identifier, parent),
	player(player), enemy(enemy), score(0), seed(0), win(false), lose(false), TWO_SECONDS(120), lengthOfHighScores(4),
	turn("Turn"), playerHp("PlayerHP"), enemyHp("EnemyHP"), continueButton("ContinueButton", "buttonImgs/continue.png"), testingVersion(true)
{
	
	//Setting continue button
	this->continueButton.SetPosition(550,200);
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
	turn.SetFont("fonts/font.ttf");
	turn.SetColor(sf::Color::White);
	turn.SetPosition(400, 50);
	turn.SetSize(50);

	playerHp.SetText(playerHpText);
	playerHp.SetFont("fonts/font2.ttf");
	playerHp.SetColor(sf::Color::Blue);
	playerHp.SetPosition(50, 100);
	playerHp.SetSize(40);

	enemyHp.SetText(enemyHpText);
	enemyHp.SetFont("fonts/font2.ttf");
	enemyHp.SetColor(sf::Color::Red);
	enemyHp.SetPosition(50, 50);
	enemyHp.SetSize(40);
	enemyTimer = TWO_SECONDS;

	lostTimer = TWO_SECONDS * 2;
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
			this->UpdateText(this->turn, "You Lose!\nScore: " + std::to_string(score));
			if (lostTimer <= 0) this->ResetGame(true);
			else lostTimer--;
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
	CheckActive(active);
	turn.RenderGameObject(window);
	playerHp.RenderGameObject(window);
	enemyHp.RenderGameObject(window);
	continueButton.RenderGameObject(window);
	continueButton.Update(window);
}

void FightManager::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	CheckActive(active);
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

void FightManager::SetGameManager(GameManager* gameManager)
{
	this->gameManager = gameManager;
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
	this->lostTimer = TWO_SECONDS * 2;
	
	//resetting pokemons
	this->player.GetPokemon()->ResetPokemon();
	this->enemy.GetPokemon()->ResetPokemon();
	
	//selecting new random pokemon
	this->player.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;
	this->enemy.SetRandomPokemon(PokemonPicker::RandomPokemon(pokemonList, seed));
	this->seed++;

	//Moving pokes into new position
	this->MovePokesIntoPos();

	if (backToMainMenu)
	{
		//Create function to compare the score gotten this turn with highscore, and update it if necessary
		int indexToPlace = this->gameManager->CompareHighScores(score, lengthOfHighScores);
		printf("index returned: %d\n", indexToPlace);
		if (this->gameManager) this->gameManager->SetHighScores(this->score, indexToPlace);
		else printf("Game Manager not found in FightManager object!\n");
		score = 0;
	}
}

void FightManager::UpdateText(TextObject& textObj, const string text)
{
	textObj.SetText(text);
}

void FightManager::InitializePokemonList()
{
	string line;
	ifstream myFile("textFiles/pokemons.txt");
	while (getline(myFile, line))
	{
		string name;
		int power, hp, hpTesting;

		//Creating a stream from the current line in the file
		stringstream lineStream(line);

		//pushing the values to the variables respectively
		lineStream >> name >> power >> hpTesting >> hp;

		//allocating memory in heap for each pokemon
		if(testingVersion) this->pokemonList.push_back(new Pokemon(name, power, hpTesting, name, "pokemonImgs/" + name + ".png"));
		else this->pokemonList.push_back(new Pokemon(name, power, hp, name, "pokemonImgs/" + name + ".png"));
	}
	myFile.close();
}

void FightManager::CheckGameStatus(const int playerLife, const int enemyLife)
{
	if (playerLife <= 0) lose = true;
	else if (enemyLife <= 0) win = true;
}
