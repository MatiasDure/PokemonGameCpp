#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.h"


using namespace std;

class Scene
{
private:
	const string identifier;
	vector<GameObject*> objectsInScene;

public: 
	Scene(const string identifier);
	void RenderScene(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void AddObject(GameObject* objToAdd);
	void RemoveObject(const string identifierOfObj);
	void HandleEvent(sf::Event& event, sf::RenderWindow& window);
	string GetIdentifier() const;
	vector<GameObject*> GetObjectsInScene() const;
	int AmountObjectsInScene() const;
};
