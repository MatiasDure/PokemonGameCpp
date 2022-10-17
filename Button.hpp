#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.hpp"

class Button : public SpriteObject
{
private:
protected:
public:
	Button(string identifier, sf::Vector2f startingPosition, string fileName, GameObject* parent = NULL);
	void HandleEvent(sf::Event& event, sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
};