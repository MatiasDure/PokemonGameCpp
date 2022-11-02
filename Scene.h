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
	bool firstRender;
	const string identifier;
	const int popForce;
	vector<GameObject*> objectsInScene;

public: 
	Scene(const string identifier, const int popForce);
	~Scene();
	void RenderScene(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void AddObject(GameObject* objToAdd);
	void RemoveObject(const string identifierOfObj);
	void HandleEvent(sf::Event& event, sf::RenderWindow& window);
	string GetIdentifier(void) const;
	int GetPopForce(void) const;
	vector<GameObject*> GetObjectsInScene(void) const;
	int AmountObjectsInScene(void) const;
};
