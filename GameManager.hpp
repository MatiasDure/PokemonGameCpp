#pragma once
#include <fstream>
#include <sstream>
#include "TextObject.hpp"
#include "Button.hpp"

class GameManager: public GameObject
{
private:
	bool displayingScores;
	int highscores[5];
	int lengthIndexHighScores;
	TextObject scores;
	Button scoresBack;
	SpriteObject scoresBackground;

public:
	GameManager(string identifier, GameObject* parent = nullptr);

	//Inherited methods
	void HandleEvent(sf::Event& event, sf::RenderWindow& window) override;
	void RenderGameObject(sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;

	void SetHighScores(int scoreToPlace, int indexToPlace);
	int CompareHighScores(int score, int index);
	void ReadHighScores(void);
	void ClearHighScores(void);
	void DisplayHighScore(void);
	void HideHighScore(void);
	void UpdateHighScoreText(void);

	bool GetDisplayingScores(void) const;
};
