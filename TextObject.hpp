#pragma once
#include "GameObject.h"
class TextObject : public GameObject
{
private:
	sf::Text textObj;
	sf::Font font;
	string text;
protected:
public:
	TextObject(string identifier, GameObject* parent = NULL);

	void SetText(const string& text);
	void SetColor(const sf::Color& color);
	void SetFont(const sf::Font& font);
	void RenderGameObject(sf::RenderWindow& window) override;

};