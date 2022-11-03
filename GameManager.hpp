#pragma once
#include <fstream>
#include <sstream>
#include <iostream>

class GameManager
{
private:
	static GameManager* Manager;
	unsigned int highscores[5];
	unsigned int currentScore;
	GameManager();
	
public:
	static GameManager* GetInstance();
	void SetHighScores();
	void ReadHighScores();
	void ResetGame();
	void NextLevel();
	
	//getting rid of the copy and assign operators
	GameManager(const GameManager& manager) = delete;
	GameManager operator=(const GameManager& manager) = delete;
};

//GameManager* GameManager::Manager = 0;


