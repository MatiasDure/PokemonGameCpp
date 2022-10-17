#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class GameObject
{

private:
	GameObject* parent;
	const string identifier;
	vector<GameObject*> children;

protected:
	sf::Vector2f position;

public:
	//Constructors
	GameObject(string identifier, sf::Vector2f startingPosition, GameObject* parent = NULL);
	GameObject(const GameObject& other);

	//Destructor
	~GameObject();

	//dont want to create a copy or modify the game object passed in so we are declaring it a const and asking for the reference
	void AddChild(GameObject* objToAdd);
	void RemoveChild(GameObject& objToRemove);
	void SetParent(GameObject* parent);
	void RemoveParent();

	virtual void HandleEvent(sf::Event& event, sf::RenderWindow& window) {};
	void MoveObj(const sf::Vector2f vec);
	void MoveObj(const float x, const float y);
	bool HasParent() const;

	virtual void RenderGameObject(sf::RenderWindow& window) {};

	//Getters
	string GetIdentifier() const;
	sf::Vector2f GetPosition() const;
	GameObject* GetParent() const;

	//overloading comparison operator
	bool operator == (const GameObject& other) const;
	
	virtual void Update(sf::RenderWindow& window);
};