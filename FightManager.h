#pragma once
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "TextObject.hpp"
#include "Button.hpp"

class FightManager: public GameObject
{
private:
	bool win, lose, increasedPoint;
	int highscores[5];
	int lengthOfHighScores;
	int score;
	int seed;
	const int TWO_SECONDS;
	int enemyTimer;
	class GameManager* gameManager;
	Player& player;
	Enemy& enemy;
	TextObject turn, playerHp, enemyHp;
	Button continueButton;
	string turnText, playerHpText, enemyHpText;
	sf::Font font;
	vector<class Pokemon*> pokemonList;
	void DecideStartingPlayer(void);
	void InitializePokemonList(void);
	void CheckGameStatus(const int playerLife, const int enemyLife);

public:
	FightManager(Player& player, Enemy& enemy, string identifier, GameObject* parent = NULL);
	~FightManager() override;
	/*void SetHighScores(int indexToPlace);
	int CompareHighScores(int score, int index);
	void ReadHighScores(void);*/
	void SwitchTurns(void);
	void ResetGame(bool backToMainMenu);
	void NextLevel(void);
	void UpdateText(TextObject& textObj, const string text);
	void Update(sf::RenderWindow& window) override;
	void RenderGameObject(sf::RenderWindow& window) override;
	void HandleEvent(sf::Event& event, sf::RenderWindow& window)override;
	void MovePokesIntoPos();
	void SetGameManager(GameManager* gameManager);

	//getters
	bool gameWon(void)const;
	bool gameLost(void)const;
};