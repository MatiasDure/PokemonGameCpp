#include <SFML/Graphics.hpp>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Pokemon.hpp"
#include "SceneManager.h"
#include "GameManager.hpp"
#include "TextObject.hpp"
#include "FightManager.h"

using namespace std;

void CreateScenes(SceneManager& manager, sf::RenderWindow& window, GameManager& gameManager);

int main()
{
	//giving current system time as seed
	srand(time(0));

	//creating window
	sf::RenderWindow window(sf::VideoMode(1200,720),"MyCppGame!");
	window.setFramerateLimit(60);
	
	const string gameManagerIdentifier = "GameManager";
	GameManager gameManager(gameManagerIdentifier);
	SceneManager sceneManager;
	CreateScenes(sceneManager, window, gameManager);
	//fps
	//float fps;
	//sf::Clock clock = sf::Clock::Clock();
	//sf::Time previousTime = clock.getElapsedTime();
	//sf::Time currentTime;

	//running game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			sceneManager.HandleEvent(event, window);
		}
		sceneManager.RenderScene(window);
		sceneManager.Update(window);
		//Printing fps
		//currentTime = clock.getElapsedTime();
		//fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
		//std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
		//previousTime = currentTime;
	}

	return 0;
}

void CreateScenes(SceneManager& manager, sf::RenderWindow& window, GameManager& gameManager)
{

	sf::Vector2u windowSize = window.getSize();

	//Main menu scene
	Scene* mainMenuScene = new Scene("MainMenu", 0);

	int yOffsetMainMenu = 120;

	//Buttons
	//Switching to the fighting scene
	Button* start = new Button("StartButton", "start.png");
	start->SetBehavior([&manager, &gameManager]() {
		if (gameManager.GetDisplayingScores()) return;
		manager.StackScene("Fight");
		});
	start->SetPosition(windowSize.x/2, windowSize.y/5 + yOffsetMainMenu);
	start->SetScale(0.8f, 0.8f);

	Button* scores = new Button("ScoresButton", "scores.png");
	scores->SetBehavior([&gameManager]() {
		if (gameManager.GetDisplayingScores()) return;
		gameManager.DisplayHighScore();
		});
	scores->SetPosition(windowSize.x / 2, windowSize.y / 5 + yOffsetMainMenu * 2);
	scores->SetScale(0.8f, 0.8f);

	//Resetting highscore file
	Button* erase = new Button("EraseButton", "clearData.png");
	erase->SetBehavior([&gameManager]() {
		if (gameManager.GetDisplayingScores()) return;
		gameManager.ClearHighScores();
		});
	erase->SetPosition(windowSize.x / 2, windowSize.y / 5 + yOffsetMainMenu * 3);
	erase->SetScale(0.8f, 0.8f);

	//Quit game
	Button* quit = new Button("QuitButton", "quit.png");
	quit->SetBehavior([&window, &gameManager]() {
		if (gameManager.GetDisplayingScores()) return;
		window.close();
		});
	quit->SetPosition(windowSize.x / 2, windowSize.y / 5 + yOffsetMainMenu * 4);
	quit->SetScale(0.8f, 0.8f);

	//Title
	TextObject* title = new TextObject("Title");
	title->SetText("Pokemon C++ Game");
	title->SetColor(sf::Color::White);
	title->SetFont("font.ttf");
	title->SetSize(80);
	sf::FloatRect titleBounds = title->GetTextBounds();
	title->SetPosition(windowSize.x/2 - titleBounds.width/2, windowSize.y/20);

	//Adding objects to the scene
	mainMenuScene->AddObject(title);
	mainMenuScene->AddObject(start);
	mainMenuScene->AddObject(scores);
	mainMenuScene->AddObject(erase);
	mainMenuScene->AddObject(quit);
	mainMenuScene->AddObject(&gameManager);

	//Fight scene
	Scene* fightScene = new Scene("Fight", 1);

	int yOffsetFight = 100;
	int xOffsetFight = 200;

	//background
	SpriteObject* background = new SpriteObject("Background", "fightBackground.png");

	//Pokemon trainers
	Player* player = new Player("Player", "player.png");
	Enemy* enemy = new Enemy("Enemy", "enemy.png", player);
	player->SetTarget(enemy);

	//Game manager
	FightManager* game = new FightManager(*player, *enemy, "Game");
	game->SetGameManager(&gameManager);
	
	//buttons
	
	//attack button for player
	Button* attack = new Button("AttackButton", "attack.png");
	attack->SetBehavior([player, game]() {
		if (!player->GetTurn() || game->gameLost() || game->gameWon()) return;
		player->Attack(*player->GetTarget());
		game->SwitchTurns();
		});
	attack->SetPosition(windowSize.x / 2 + xOffsetFight, 580);
	attack->SetScale(0.6f, 0.6f);

	//Heal button for player
	Button* heal = new Button("HealButton", "heal.png");
	heal->SetBehavior([player, game]() {
		if (!player->GetTurn() || game->gameLost() || game->gameWon()) return;
		int amountHeal = 30;
		player->Heal(amountHeal);
		game->SwitchTurns();
		});
	heal->SetPosition(windowSize.x / 2 + xOffsetFight + 250, 580);
	heal->SetScale(0.6f, 0.6f);

	//skip button for player
	Button* skip = new Button("SkipButton", "skip.png");
	skip->SetBehavior([player, game]() {
		if (!player->GetTurn() || game->gameLost() || game->gameWon()) return;
		game->SwitchTurns();
		});
	skip->SetPosition(windowSize.x / 2 + xOffsetFight, 680);
	skip->SetScale(0.6f, 0.6f);

	//Switching back to main menu
	Button* back = new Button("BackButton", "back.png");
	back->SetBehavior([&manager, game]() {
		game->ResetGame(true);
		manager.PopScene();
		});
	back->SetPosition(windowSize.x / 2 + xOffsetFight + 250, 680);
	back->SetScale(0.6f, 0.6f);

	//Adding objects to fight scene
	fightScene->AddObject(background);
	fightScene->AddObject(game);
	fightScene->AddObject(player);
	fightScene->AddObject(enemy);
	fightScene->AddObject(back);
	fightScene->AddObject(attack);
	fightScene->AddObject(heal);
	fightScene->AddObject(skip);

	//Adding created scenes to the manager
	manager.AddScene(mainMenuScene);
	manager.AddScene(fightScene);
}