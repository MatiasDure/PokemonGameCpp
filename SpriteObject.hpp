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
	float originX, originY;
	float scaleX, scaleY;

public:
	SpriteObject(string identifier, string fileName, GameObject* parent = NULL);
	void RenderGameObject(sf::RenderWindow& window) override;
	void HandleEvent(sf::Event& event, sf::RenderWindow& window) override {};
	void Update(sf::RenderWindow& window) override;
	void MoveObj(const sf::Vector2f vec) override;
	void MoveObj(const float x, const float y) override;
	void SetPosition(const float x, const float y) override;
	void SetOriginXY(const float x, const float y);
	void SetScale(const float x, const float y) override;
	void ScaleByMultiplier(const float x, const float y);
	void UpdateBoundary();
	
	//getters
	float GetWidth(void)const;
	float GetHeight(void)const;
	string GetFileName(void)const;
	sf::Sprite GetSpriteObj(void)const;
};