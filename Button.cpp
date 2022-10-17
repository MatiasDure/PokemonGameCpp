#include "Button.hpp"

Button::Button(string identifier, sf::Vector2f startingPosition, string fileName, GameObject* parent)
	: SpriteObject(identifier, startingPosition,fileName,parent) {}

void Button::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	if (spriteBoundary.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
	{
		if (event.type == sf::Event::MouseButtonPressed) window.close();
	}
}

void Button::Update(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (spriteBoundary.contains(mousePos.x, mousePos.y))
	{
		sprite.setScale(1.5f, 1.5f);
	}
	else
	{
		sprite.setScale(1, 1);
	}
}