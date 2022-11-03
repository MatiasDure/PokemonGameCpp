#include "SpriteObject.hpp"

SpriteObject::SpriteObject(string identifier, string fileName, GameObject* parent) 
	: GameObject(identifier, parent), originX(0), originY(0), scaleX(1), scaleY(1)
{
	if (!this->texture.loadFromFile(fileName))
	{
		std::cout << "File " << identifier <<" was not loaded correctly" << endl;
		return;
	}
	std::cout << "File " << identifier << " loaded successfully" << endl;
	this->fileName = fileName;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(position);
	//To get the properties of the rectangle containing the image
	spriteBoundary = this->sprite.getGlobalBounds();
}

void SpriteObject::RenderGameObject(sf::RenderWindow& window)
{
	if (!active) return;
	window.draw(this->sprite);
}

void SpriteObject::Update(sf::RenderWindow& window) {}

void SpriteObject::MoveObj(const sf::Vector2f vec)
{
	MoveObj(vec.x, vec.y);
}

void SpriteObject::MoveObj(const float x, const float y)
{
	position.x += x;
	position.y += y;
	this->SetOriginXY(position.x, position.y);
	this->sprite.setPosition(position);
	this->UpdateBoundary();
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->MoveObj(x, y);
	}
}

void SpriteObject::SetPosition(const float x, const float y)
{
	this->SetOriginXY(x, y);
	position.x = x - spriteBoundary.width/2;
	position.y = y - spriteBoundary.height/2;
	this->sprite.setPosition(position);
	this->UpdateBoundary();
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->MoveObj(x, y);
	}
}

void SpriteObject::UpdateBoundary()
{
	spriteBoundary = this->sprite.getGlobalBounds();
}

void SpriteObject::SetOriginXY(const float x, const float y)
{
	originX = x;
	originY = y;
}

void SpriteObject::SetScale(const float x, const float y)
{
	this->scaleX = x;
	this->scaleY = y;
}

void SpriteObject::ScaleByMultiplier(const float x, const float y)
{
	this->sprite.setScale(scaleX * x, scaleY * y);
	this->UpdateBoundary();
}

string SpriteObject::GetFileName(void) const
{
	return this->fileName;
}

sf::Sprite SpriteObject::GetSpriteObj(void) const
{
	return this->sprite;
}

float SpriteObject::GetWidth(void) const
{
	return this->spriteBoundary.width;
}

float SpriteObject::GetHeight(void) const
{
	return this->spriteBoundary.height;
}