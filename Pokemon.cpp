#include "Pokemon.hpp"

Pokemon::Pokemon(string name, int power, int hp, string identifier, string fileName, GameObject* parent)
	:SpriteObject(identifier, fileName, parent),
	pokeName(name), power(power), hp(hp), originalHp(hp) {}

Pokemon::Pokemon(Pokemon& other) 
	:Pokemon(other.GetName(), other.GetPower(), other.GetHP(), other.GetName(),	other.GetFileName(), 
		other.GetParent()) {}

void Pokemon::TakeDamage(int damage)
{
	this->hp -= damage;
	hp = hp < 0 ? 0 : hp;
}

void Pokemon::ResetPokemon(void)
{
	hp = originalHp;
}

string Pokemon::GetName(void) const
{
	return this->pokeName;
}
int Pokemon::GetOriginalHp(void) const
{
	return this->originalHp;
}
int Pokemon::GetPower(void) const
{
	return this->power;
}
int Pokemon::GetHP(void) const
{
	return this->hp;
}

std::ostream& operator<<(std::ostream& stream, const Pokemon& poke)
{
	return stream << "Pokemon:\nName: " << poke.GetName() << "\nPower: " << poke.GetPower()
		<< "\nHP: " << poke.GetHP() << endl;
}