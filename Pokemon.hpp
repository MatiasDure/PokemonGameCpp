#pragma once
#include "SpriteObject.hpp"

class Pokemon : public SpriteObject
{
private:
	string pokeName;
	const int originalHp;
	int power, hp, stamina;
	friend ostream& operator <<(ostream& outputStream, const Pokemon& p);
public:
	//constructor 
	Pokemon(string name, int power, int hp, int stamina, string identifier,	string fileName, GameObject* parent = NULL);
	Pokemon(Pokemon& other);

	void TakeDamage(int damage);
	void ResetPokemon();

	//getters
	string GetName(void) const;
	int GetOriginalHp(void) const;
	int GetHP(void) const;
	int GetPower(void) const;
	int GetStamina(void) const;

};