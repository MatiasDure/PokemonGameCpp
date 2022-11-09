#include "GameManager.hpp"

GameManager::GameManager(string identifier, GameObject* parent) :
	GameObject(identifier, parent), 
	scores("Scores"), scoresBack("BackManagerButton", "buttonImgs/back.png"), scoresBackground("ScoresBackground","bgImgs/scoresBackground.jpg")
{
	lengthIndexHighScores = 4;
	HideHighScore();
	ReadHighScores();
	UpdateHighScoreText();

	//setting up score text
	this->scores.SetColor(sf::Color::White);
	this->scores.SetFont("fonts/font.ttf");
	this->scores.SetSize(50);
	this->scores.SetPosition(450, 200);

	//setting up back button
	this->scoresBack.SetScale(0.4f, 0.4f);
	this->scoresBack.SetPosition(1000, 140);
	this->scoresBack.SetBehavior([this]() {
		this->HideHighScore();
		});
	
	//setting up background
	this->scoresBackground.SetPosition(600, 355);
	this->scoresBackground.SetColor(sf::Color::Color(255, 255, 255, 245));
}

void GameManager::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	CheckActive(this->active);
	scoresBack.HandleEvent(event, window);
}

void GameManager::RenderGameObject(sf::RenderWindow& window)
{
	CheckActive(this->active);
	scoresBackground.RenderGameObject(window);
	scoresBack.RenderGameObject(window);
	scores.RenderGameObject(window);
	
}

void GameManager::Update(sf::RenderWindow& window)
{
	CheckActive(this->active);
	scoresBackground.Update(window);
	scoresBack.Update(window);
	scores.Update(window);
}

//Updating highscore and file with new score
void GameManager::SetHighScores(int scoreToPlace, int indexToPlace )
{
	for (int i = lengthIndexHighScores; i > indexToPlace - 1; i--)
	{
		if (i != lengthIndexHighScores) highscores[i + 1] = highscores[i];
		highscores[i] = scoreToPlace;
	}

	ofstream myFile("textFiles/highscores.txt", ios::trunc);

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

//Reading highscore from file
void GameManager::ReadHighScores(void)
{
	string line;
	ifstream myFile("textFiles/highscores.txt");
	int i = 0;
	while (getline(myFile, line) && i < 5)
	{
		stringstream lineStream(line);
		lineStream >> this->highscores[i++];
	}
}

//Resetting Highscore file with 0s
void GameManager::ClearHighScores(void)
{
	ofstream myFile("textFiles/highscores.txt", ios::trunc);
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

void GameManager::DisplayHighScore(void)
{
	this->displayingScores = true;
	ReadHighScores();
	UpdateHighScoreText();
	scoresBackground.SetActive(true);
	scores.SetActive(true);
	scoresBack.SetActive(true);
}

void GameManager::HideHighScore(void)
{
	this->displayingScores = false;
	scoresBackground.SetActive(false);
	scores.SetActive(false);
	scoresBack.SetActive(false);
}

void GameManager::UpdateHighScoreText(void)
{
	this->scores.SetText("HIGHSCORES\n\t1. " + to_string(highscores[0]) +
		"\n\t2. " + to_string(highscores[1]) +
		"\n\t3. " + to_string(highscores[2]) +
		"\n\t4. " + to_string(highscores[3]) +
		"\n\t5. " + to_string(highscores[4]));
}

bool GameManager::GetDisplayingScores(void) const
{
	return this->displayingScores;
}
