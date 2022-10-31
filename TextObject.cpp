#include "TextObject.hpp"

TextObject::TextObject(string identifier, GameObject* parent) 
	: GameObject(identifier, parent)
{
}

void TextObject::SetText(const string& text)
{
	this->text = text;
	this->textObj.setString(text);
}

void TextObject::SetColor(const sf::Color& color)
{
	this->textObj.setFillColor(color);
}

void TextObject::SetFont(const string& font)
{
	if (!this->font.loadFromFile(font))
	{
		cout << "Not able to load font file!" << endl;
		return;
	};
	this->textObj.setFont(this->font);
}

void TextObject::SetPosition(const float& x, const float& y)
{
	textObj.setPosition(x, y);
}

void TextObject::SetSize(const int x)
{
	this->textObj.setCharacterSize(x);
}

void TextObject::RenderGameObject(sf::RenderWindow& window)
{
	window.draw(this->textObj);
}

sf::Text TextObject::GetTextObject(void) const
{
	return textObj;
}
