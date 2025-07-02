#ifndef GHOST_POKEMON_H
#define GHOST_POKEMON_H

#include "Pokemon.h"

class GhostPokemon : public Pokemon
{
public:
    GhostPokemon(int level = 1);

    void useSkill(std::shared_ptr<Pokemon> target) override;

    // For serialization
    GhostPokemon(std::string name, PokeType type, int level, int experience, int maxHealth, int currentHealth, int maxMagic, int currentMagic, int baseAttack, int magicRegen, int defense, double evasionRate, double criticalRate);

    static std::shared_ptr<GhostPokemon> fromJson(const nlohmann::json &j);
};

#endif // GHOST_POKEMON_H