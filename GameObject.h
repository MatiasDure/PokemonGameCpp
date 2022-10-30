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

protected:
	sf::Vector2f position;
	vector<GameObject*> children;

public:
	//Constructors
	GameObject(string identifier, GameObject* parent = NULL);
	GameObject(const GameObject& other);

	//Destructor
	~GameObject();

	void AddChild(GameObject* objToAdd);
	void RemoveChild(GameObject& objToRemove);
	void SetParent(GameObject* parent);
	void RemoveParent();

	virtual void HandleEvent(sf::Event& event, sf::RenderWindow& window) {};
	virtual void MoveObj(const sf::Vector2f vec);
	virtual void MoveObj(const float x, const float y);
	virtual void SetPosition(const float x, const float y);
	virtual void SetScale(const float x, const float y) {};
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