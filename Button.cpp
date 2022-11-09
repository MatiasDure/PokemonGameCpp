#include "Button.hpp"

Button::Button(string identifier, string fileName, GameObject* parent)
	: SpriteObject(identifier, fileName, parent), mouseHover(false) {}

void Button::HandleEvent(sf::Event& event, sf::RenderWindow& window)
{
	CheckActive(active);
	if (mouseHover && event.type == sf::Event::MouseButtonPressed)
	{
		try
		{
			behavior();
		}
		catch(exception e) {
			std::cout<< "No function passed to button!" << endl;
		}
	}
}

void Button::Update(sf::RenderWindow& window)
{
	CheckActive(active);
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (spriteBoundary.contains(mousePos.x, mousePos.y))
	{
		mouseHover = true;
		this->ScaleByMultiplier(1.1f, 1.1f);
	}
	else
	{
		mouseHover = false;
		this->ScaleByMultiplier(1.0f, 1.0f);
	}
}

void Button::SetBehavior(const std::function<void()> behavior)
{
	this->behavior = behavior;
}