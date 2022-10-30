#pragma once
#include "SpriteObject.hpp"

class Pokemon : public SpriteObject
{
private:
	string pokeName;
	int power, hp, stamina;
	friend ostream& operator <<(ostream& outputStream, const Pokemon& p);
public:
	//constructor 
	Pokemon(string name, int power, int hp, int stamina, string identifier,	string fileName, GameObject* parent = NULL);
	Pokemon(Pokemon& other);

	//getters
	string GetName() const;
	int GetHP() const;
	int GetPower() const;
	int GetStamina() const;

};