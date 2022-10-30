#pragma once
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Pokemon.hpp"

class GameManager: public GameObject
{
private:
	bool win, lose;
	int highscores[5];
	int score;
	int seed;
	Player& player;
	Enemy& enemy;
	vector<Pokemon*> pokemonList;
	
public:
	GameManager(Player& player, Enemy& enemy, string identifier, GameObject* parent = NULL);
	void ResetGame();
	void NextLevel();
	void SetHighScores();
	void ReadHighScores();
	void InitializePokemonList();
	void Update();
};
