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

using namespace std;

//Scene DecideScene(const int currentIndex, const vector<Pokemon*>& pokemonList)
//{
//	const int i = 0;
//	Scene scene("Scene"+currentIndex , i);
//	switch (currentIndex)
//	{
//		case 0:
//		{
//			scene.AddObject(new SpriteObject("background", sf::Vector2f(0, 0), "background.jpg"));
//			scene.AddObject(new Player("Player", sf::Vector2f(30, 5), "player.png", pokemonList, 5));
//			scene.AddObject(new Enemy("Enemy", sf::Vector2f(330, 5), "enemy.png", pokemonList,6));
//			break;
//		}
//		case 1:
//		{
//			GameObject ob("hey", sf::Vector2f(0, 0));
//			scene.AddObject(&ob);
//			scene.AddObject(&ob);
//			scene.AddObject(&ob);
//			break;
//		}
//		case 2:
//			break;
//		default:
//			break;
//	}
//	return scene;
//}


void CreateScenes(SceneManager& manager, sf::RenderWindow& window);
void InitializePokemonList(vector<Pokemon*>& list);

int main()
{
	//creating window
	sf::RenderWindow window(sf::VideoMode(1200,720),"MyGame");
	window.setFramerateLimit(60);

	//initializing pokemon list from text file
	//vector<Pokemon*> pokemonList;
	//InitializePokemonList(pokemonList);

	SceneManager sceneManager;
	//CreateScenes(sceneManager, pokemonList, window);
	CreateScenes(sceneManager, window);
	//fps
	//float fps;
	//sf::Clock clock = sf::Clock::Clock();
	//sf::Time previousTime = clock.getElapsedTime();
	//sf::Time currentTime;

	//printing pokemon list
	//for (int i = 0; i < pokemonList.size();i++)
	//{
	//	cout << *pokemonList[i];
	//}

	//decide which scene to use
	//int currentSceneIndex = 0;
	//Scene currentScene = DecideScene(0, pokemonList);
	 
	//cout << currentScene.AmountObjectsInScene();
	
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

void InitializePokemonList(vector<Pokemon*>& list)
{
	string line;
	ifstream myFile("pokemons.txt");
	while (getline(myFile, line))
	{
		string name;
		int power, hp, stamina;

		//Creating a stream from the current line in the file
		stringstream lineStream(line);

		//pushing the values to the variables respectively
		lineStream >> name >> power >> hp >> stamina;

		//allocating memory in heap for each pokemon
		list.push_back(new Pokemon(name,power,hp,stamina,name,name+".png"));
	}
	myFile.close();
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
				myFile << i << ".\n";
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

	//Adding objects to the scene
	scene1->AddObject(start);
	scene1->AddObject(erase);
	scene1->AddObject(quit);

	//Fight scene
	Scene* scene2 = new Scene("Fight", 1);

	//background
	SpriteObject* background = new SpriteObject("Background", "background.jpg");

	//Pokemon trainers
	Player* player = new Player("Player", "player.png");
	Enemy* enemy = new Enemy("Enemy", "enemy.png");

	//Game manager
	GameManager* game = new GameManager(*player, *enemy, "Game");
	
	//buttons
	//Switching back to main menu
	Button* back = new Button("Back", "start.png");
	back->SetBehavior([&manager, game]() {
		game->ResetGame();
		manager.PopScene();
		});
	back->SetPosition(1140, 80);
	back->SetScale(0.6f, 0.6f);

	//Adding objects to the scene
	scene2->AddObject(game);
	scene2->AddObject(background);
	scene2->AddObject(player);
	scene2->AddObject(enemy);
	scene2->AddObject(back);

	//Adding created scenes to the manager
	manager.AddScene(scene1);
	manager.AddScene(scene2);
}