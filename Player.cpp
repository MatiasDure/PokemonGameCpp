#include "Player.hpp"

Player::Player(string identifier, sf::Vector2f startingPosition, string fileName, const vector<Pokemon*>& pokemonList, const int seed, GameObject* parent)
	:PokemonTrainer(identifier, startingPosition, fileName, pokemonList, seed, parent) {}