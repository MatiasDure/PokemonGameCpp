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
	void SetFont(const string& file);
	void SetPosition(const float& x, const float& y);
	void SetSize(const int x);
	void RenderGameObject(sf::RenderWindow& window) override;

	sf::Text GetTextObject(void) const;
	sf::FloatRect GetTextBounds(void);
};

