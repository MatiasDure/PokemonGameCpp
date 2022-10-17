#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"

class SpriteObject : public GameObject
{
private:
	string fileName;
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect spriteBoundary;

public:
	SpriteObject(string identifier, sf::Vector2f startingPosition, string fileName, GameObject* parent = NULL);
	void RenderGameObject(sf::RenderWindow& window) override;
	void HandleEvent(sf::Event& event, sf::RenderWindow& window) override {};
	void Update(sf::RenderWindow& window) override;
	string GetFileName() const;
};