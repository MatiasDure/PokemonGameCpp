#include "Pokemon.hpp"

Pokemon::Pokemon(string name, int power, int hp, int stamina, string identifier, string fileName, GameObject* parent)
	:SpriteObject(identifier, fileName, parent),
	pokeName(name), power(power), hp(hp), stamina(stamina), originalHp(hp) {}

Pokemon::Pokemon(Pokemon& other) 
	:Pokemon(other.GetName(), other.GetPower(), other.GetHP(), other.GetStamina(), other.GetName(),	other.GetFileName(), 
		other.GetParent()) {}

void Pokemon::TakeDamage(int damage)
{
	this->hp -= damage;
}

void Pokemon::ResetPokemon()
{
	hp = originalHp;
}

string Pokemon::GetName() const
{
	return this->pokeName;
}
int Pokemon::GetOriginalHp(void) const
{
	return this->originalHp;
}
int Pokemon::GetPower() const
{
	return this->power;
}
int Pokemon::GetHP() const
{
	return this->hp;
}
int Pokemon::GetStamina() const
{
	return this->stamina;
}

std::ostream& operator<<(std::ostream& stream, const Pokemon& poke)
{
	return stream << "Pokemon:\nName: " << poke.GetName() << "\nPower: " << poke.GetPower()
		<< "\nHP: " << poke.GetHP() << "\nStamina: " << poke.GetStamina() << endl;
}