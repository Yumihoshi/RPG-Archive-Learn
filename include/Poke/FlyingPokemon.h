#ifndef FLYING_POKEMON_H
#define FLYING_POKEMON_H

#include "Pokemon.h"

class FlyingPokemon : public Pokemon
{
public:
    FlyingPokemon(int level = 1);

    void useSkill(std::shared_ptr<Pokemon> target) override;

    // For serialization
    FlyingPokemon(std::string name, PokeType type, int level, int experience, int maxHealth, int currentHealth, int maxMagic, int currentMagic, int baseAttack, int magicRegen, int defense, double evasionRate, double criticalRate);

    static std::shared_ptr<FlyingPokemon> fromJson(const nlohmann::json &j);
};

#endif // FLYING_POKEMON_H