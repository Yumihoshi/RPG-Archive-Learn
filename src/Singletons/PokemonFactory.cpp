#include "../../include/Singletons/PokemonFactory.h"
#include "../../include/Poke/Pokemon.h"
#include "../../include/Poke/FirePokemon.h"
#include "../../include/Poke/GrassPokemon.h"
#include "../../include/Poke/IcePokemon.h"
#include "../../include/Poke/FlyingPokemon.h"
#include "../../include/Poke/GhostPokemon.h"

std::shared_ptr<Pokemon>
PokemonFactory::createPokemon(Pokemon::PokeType type, int level)
{
    switch (type)
    {
        case Pokemon::FIRE:
            return std::make_shared<FirePokemon>(level);
        case Pokemon::GRASS:
            return std::make_shared<GrassPokemon>(level);
        case Pokemon::ICE:
            return std::make_shared<IcePokemon>(level);
        case Pokemon::FLYING:
            return std::make_shared<FlyingPokemon>(level);
        case Pokemon::GHOST:
            return std::make_shared<GhostPokemon>(level);
        default:
            throw std::runtime_error(
                    "尝试创建一个未实现的 Pokemon 类型。");
    }
}

std::shared_ptr<Pokemon> PokemonFactory::createPokemon(const nlohmann::json &j)
{
    Pokemon::PokeType type = static_cast<Pokemon::PokeType>(j["type"].get<int>());
    switch (type)
    {
        case Pokemon::FIRE:
            return FirePokemon::fromJson(j);
        case Pokemon::GRASS:
            return GrassPokemon::fromJson(j);
        case Pokemon::ICE:
            return IcePokemon::fromJson(j);
        case Pokemon::FLYING:
            return FlyingPokemon::fromJson(j);
        case Pokemon::GHOST:
            return GhostPokemon::fromJson(j);
        default:
            throw std::runtime_error(
                    "尝试创建一个未实现的 Pokemon 类型。");
    }
}
