#ifndef POKEMON_FACTORY_H
#define POKEMON_FACTORY_H

#include <memory>
#include "../Poke/Pokemon.h"
#include "../Poke/FirePokemon.h"
#include "../Poke/GrassPokemon.h"
#include "../Poke/IcePokemon.h"
#include "../Poke/FlyingPokemon.h"
#include "../Poke/GhostPokemon.h"

class PokemonFactory
{
public:
    static std::shared_ptr<Pokemon> createPokemon(Pokemon::PokeType type, int level = 1);
    static std::shared_ptr<Pokemon> createPokemon(const nlohmann::json &j);
};

#endif // POKEMON_FACTORY_H