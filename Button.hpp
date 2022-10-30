#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.hpp"
#include <functional>

class Button : public SpriteObject
{
private:
	std::function<void()> behavior;
	bool mouseHover;
protected:
public:
	Button(string identifier, string fileName, GameObject* parent = NULL);
	void HandleEvent(sf::Event& event, sf::RenderWindow& window) override;
	void Update(sf::RenderWindow& window) override;
	void SetBehavior(std::function<void()>);
};