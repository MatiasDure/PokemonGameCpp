#pragma once
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Pokemon.hpp"
#include <Windows.h>

class GameManager: public GameObject
{
private:
	bool win, lose;
	int highscores[5];
	int score;
	int seed;
	int enemyTimer;
	Player& player;
	Enemy& enemy;
	vector<Pokemon*> pokemonList;
	
public:
	GameManager(Player& player, Enemy& enemy, string identifier, GameObject* parent = NULL);
	void DecideStartingPlayer();
	void SwitchTurns();
	void ResetGame();
	void NextLevel();
	void SetHighScores();
	void ReadHighScores();
	void InitializePokemonList();
	void Update(sf::RenderWindow& window) override;
};
