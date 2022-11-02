#pragma once
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Pokemon.hpp"
#include "TextObject.hpp"
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
	TextObject turn, playerHp, enemyHp;
	string turnText, playerHpText, enemyHpText;
	sf::Font font;
	vector<Pokemon*> pokemonList;
	void DecideStartingPlayer(); 
	void InitializePokemonList();
	
public:
	GameManager(Player& player, Enemy& enemy, string identifier, GameObject* parent = NULL);
	~GameManager() override;
	void SetHighScores();
	void ReadHighScores();
	void SwitchTurns();
	void ResetGame();
	void NextLevel();
	void UpdateText(TextObject& textObj, string text);
	void Update(sf::RenderWindow& window) override;
	void RenderGameObject(sf::RenderWindow& window) override;
};
