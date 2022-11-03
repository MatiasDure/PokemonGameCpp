#include "GameManager.hpp"

GameManager::GameManager()
{
}

GameManager* GameManager::GetInstance()
{
	static GameManager* Manager;
	return Manager;
}

void GameManager::SetHighScores()
{
	//setting highscores
	unsigned int score = 0;
	for (unsigned short i = 4; i >= 0; i--)
	{
		unsigned int currentS = highscores[i];
		if (currentS != 0)
		{
			if (currentS < score)
			{
				highscores[i+1] = currentScore;
				highscores[i] = score;
			}
		}
	}
}

void GameManager::ReadHighScores()
{
	std::string line;
	std::ifstream myFile("highscores.txt");
	int i = 0;
	while (getline(myFile, line) && i < 5)
	{
		std::stringstream lineStream(line);
		lineStream >> this->highscores[i++];
	}
}

void GameManager::ResetGame()
{
}

void GameManager::NextLevel()
{
}
