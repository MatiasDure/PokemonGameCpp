#include "Enemy.hpp"

Enemy::Enemy(string identifier, sf::Vector2f startingPositon, string fileName, const vector<Pokemon*>& pokemonList, const int seed, GameObject* parent)
	:PokemonTrainer(identifier, startingPositon, fileName,pokemonList, seed, parent) {}