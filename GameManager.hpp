#pragma once
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "TextObject.hpp"
#include "Button.hpp"

class GameManager
{
private:
	int highscores[5];
	int lengthIndexHighScores;

public:
	GameManager();

	void SetHighScores(int scoreToPlace, int indexToPlace);
	int CompareHighScores(int score, int index);
	void ReadHighScores(void);
	void ClearHighScores(void);
};
