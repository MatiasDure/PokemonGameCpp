#include "GameManager.hpp"

GameManager::GameManager()
{
	lengthIndexHighScores = 4;
	ReadHighScores();
}

void GameManager::SetHighScores(int scoreToPlace, int indexToPlace )
{
	cout << "index to place: " << indexToPlace << endl;
	for (int i = lengthIndexHighScores; i > indexToPlace - 1; i--)
	{
		if (i != lengthIndexHighScores) highscores[i + 1] = highscores[i];
		highscores[i] = scoreToPlace;
	}

	ofstream myFile("highscores.txt", ios::trunc);

	if (myFile.is_open())
	{
		//Setting highscores
		for (int i = 0; i < lengthIndexHighScores + 1; i++)
		{
			myFile << highscores[i] << "\n";
		}
		myFile.close();
	}
	else printf("Not able to open file\n");
}

//recursive method to compare new score with scores in highscore list
int GameManager::CompareHighScores(int score, int index)
{
	if (index < 0) return 0;
	if (score > highscores[index]) CompareHighScores(score, index - 1);
	else return index + 1;
}

void GameManager::ReadHighScores(void)
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

void GameManager::ClearHighScores(void)
{
	ofstream myFile("highscores.txt", ios::trunc);
	if (myFile.is_open())
	{
		//Creating a new empty leaderboard and resetting highscores
		for (int i = 0; i < 5; i++)
		{
			myFile << 0 << "\n";
			highscores[i] = 0;
			printf("%d: %d\n",i+1, highscores[i]);
		}
		myFile.close();
	}
	else printf("Not able to open file\n");
}
