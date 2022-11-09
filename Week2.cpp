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

void CreateScenes(SceneManager& manager, sf::RenderWindow& window);

int main()
{
	//giving current system time as seed
	srand(time(0));

	//creating window
	sf::RenderWindow window(sf::VideoMode(1200,720),"MyGame");
	window.setFramerateLimit(60);

	SceneManager sceneManager;
	CreateScenes(sceneManager, window);
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

void CreateScenes(SceneManager& manager, sf::RenderWindow& window)
{
	//Main menu scene
	Scene* scene1 = new Scene("MainMenu", 0);

	//Buttons
	//Switching to the fighting scene
	Button* start = new Button("Start", "start.png");
	start->SetBehavior([&manager]() {
		manager.StackScene("Fight");
		});
	start->SetPosition(600, 300);

	//Resetting highscore file
	Button* erase = new Button("Erase", "clearData.png");
	erase->SetBehavior([]() {
		ofstream myFile("highscores.txt", ios::trunc);
		if (myFile.is_open())
		{
			//Creating a new empty leaderboard
			for (int i = 1; i < 6; i++)
			{
				myFile << 0 << "\n";
			}
			myFile.close();
		}
		else printf("Not able to open file\n");
		});
	erase->SetPosition(600, 460);

	//Quit game
	Button* quit = new Button("Quit", "quit.png");
	quit->SetBehavior([&window]() {
		window.close();
		});
	quit->SetPosition(600, 620);

	//Title
	TextObject* title = new TextObject("Title");
	title->SetText("Pokemon C++ Game");
	title->SetColor(sf::Color::White);
	title->SetFont("font.ttf");
	title->SetPosition(380,50);
	title->SetSize(80);

	//Adding objects to the scene
	scene1->AddObject(start);
	scene1->AddObject(erase);
	scene1->AddObject(quit);
	scene1->AddObject(title);

	//Fight scene
	Scene* scene2 = new Scene("Fight", 1);

	//background
	SpriteObject* background = new SpriteObject("Background", "background.jpg");

	//Pokemon trainers
	Player* player = new Player("Player", "player.png");
	Enemy* enemy = new Enemy("Enemy", "enemy.png", player);
	player->SetTarget(enemy);

	//Game manager
	FightManager* game = new FightManager(*player, *enemy, "Game");
	
	//buttons
	//Switching back to main menu
	Button* back = new Button("Back", "back.png");
	back->SetBehavior([&manager, game]() {
		game->ResetGame(true);
		manager.PopScene();
		});
	back->SetPosition(1140, 80);
	back->SetScale(0.6f, 0.6f);

	//attack button for player
	Button* attack = new Button("Attack", "attack.png");
	attack->SetBehavior([player, game]() {
		if (!player->GetTurn() || game->gameLost() || game->gameWon()) return;
		std::cout << player->GetTarget()->GetPokemon()->GetHP() << endl;
		player->Attack(*player->GetTarget());
		std::cout << player->GetTarget()->GetPokemon()->GetHP() << endl;
		game->SwitchTurns();
		});
	attack->SetPosition(1140, 280);
	attack->SetScale(0.6f, 0.6f);

	//Heal button for player
	Button* heal = new Button("Heal", "heal.png");
	heal->SetBehavior([player, game]() {
		if (!player->GetTurn() || game->gameLost() || game->gameWon()) return;
		//cout << enemy->GetPokemon()->GetHP() << endl;
		std::cout << player->GetPokemon()->GetHP() << endl;
		player->Heal(30);
		std::cout << player->GetPokemon()->GetHP() << endl;
		//cout << enemy->GetPokemon()->GetHP() << endl;
		game->SwitchTurns();
		});
	heal->SetPosition(1140, 380);
	heal->SetScale(0.6f, 0.6f);

	//skip button for player
	Button* skip = new Button("Skip", "skip.png");
	skip->SetBehavior([player, game]() {
		if (!player->GetTurn() || game->gameLost() || game->gameWon()) return;
		game->SwitchTurns();
		});
	skip->SetPosition(1140, 480);
	skip->SetScale(0.6f, 0.6f);

	//Button* continueButton = new Button("Continue", "start.png");
	//skip->SetBehavior([game]() {
	//	if (!game->gameWon()) return;
	//		
	//	});
	//skip->SetPosition(640, 480);
	//skip->SetScale(0.6f, 0.6f);

	//Adding objects to the scene
	scene2->AddObject(background);
	scene2->AddObject(game);
	scene2->AddObject(player);
	scene2->AddObject(enemy);
	scene2->AddObject(back);
	scene2->AddObject(attack);
	scene2->AddObject(heal);
	scene2->AddObject(skip);

	//Adding created scenes to the manager
	manager.AddScene(scene1);
	manager.AddScene(scene2);
}