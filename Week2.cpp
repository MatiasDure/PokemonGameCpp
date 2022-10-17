#include <SFML/Graphics.hpp>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "Scene.h"
#include "Button.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Pokemon.hpp"

using namespace std;

Scene DecideScene(const int currentIndex, const vector<Pokemon*>& pokemonList)
{
	Scene scene("Scene"+currentIndex);
	switch (currentIndex)
	{
		case 0:
		{
			scene.AddObject(new SpriteObject("background", sf::Vector2f(0, 0), "background.jpg"));
			scene.AddObject(new Player("Player", sf::Vector2f(30, 5), "player.png", pokemonList, 5));
			scene.AddObject(new Enemy("Enemy", sf::Vector2f(330, 5), "enemy.png", pokemonList,6));
			break;
		}
		case 1:
		{
			GameObject ob("hey", sf::Vector2f(0, 0));
			scene.AddObject(&ob);
			scene.AddObject(&ob);
			scene.AddObject(&ob);
			break;
		}
		case 2:
			break;
		default:
			break;
	}
	return scene;
}

void InitializePokemonList(vector<Pokemon*>& list);

int main()
{
	//initializing pokemon list from text file
	vector<Pokemon*> pokemonList;
	InitializePokemonList(pokemonList);

	//printing pokemon list
	//for (int i = 0; i < pokemonList.size();i++)
	//{
	//	cout << *pokemonList[i];
	//}

	//decide which scene to use
	int currentSceneIndex = 0;
	Scene currentScene = DecideScene(currentSceneIndex, pokemonList);
	
	cout << currentScene.AmountObjectsInScene();

	//creating window
	sf::RenderWindow window(sf::VideoMode(800,600),"MyGame");

	//running game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			currentScene.HandleEvent(event, window);
		}
		currentScene.RenderScene(window);
	}

	//week 3 assignment
	/*GameObject obj("parent", sf::Vector2f(1,2));
	cout << "starting position" << endl;
	cout << obj.GetIdentifier() << ": " << obj.GetPosition().x << endl;
	GameObject obj2("child", sf::Vector2f(2, 4));
	obj.AddChild(&obj2);
	cout << obj2.GetIdentifier() << ": " << obj2.GetPosition().x << endl << endl;
	obj.MoveObj(2,3);
	cout << "moving parent x +2" << endl;
	cout << obj.GetIdentifier() << ": " << obj.GetPosition().x << endl;
	cout << obj2.GetIdentifier() << ": " << obj2.GetPosition().x <<endl << endl;
	cout << "removing child from parent\n" << endl;
	obj2.RemoveParent();
	cout << "moving parent x +10" << endl;
	obj.MoveObj(10, 0);
	cout << obj.GetIdentifier() << ": " << obj.GetPosition().x << endl;
	cout << obj2.GetIdentifier() << ": " << obj2.GetPosition().x << endl;*/
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
		stringstream lineStream(line);
		lineStream >> name >> power >> hp >> stamina;
		list.push_back(new Pokemon(name,power,hp,stamina,name,sf::Vector2f(0,0),name+".png"));
	}
}