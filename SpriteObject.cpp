#include "SpriteObject.hpp"

SpriteObject::SpriteObject(string identifier, sf::Vector2f startingPosition, string fileName, GameObject* parent) 
	: GameObject(identifier,startingPosition, parent)
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
	window.draw(this->sprite);
}

void SpriteObject::Update(sf::RenderWindow& window)
{
}

string SpriteObject::GetFileName() const
{
	return this->fileName;
}