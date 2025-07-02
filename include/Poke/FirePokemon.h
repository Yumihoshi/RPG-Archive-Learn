#ifndef FIRE_POKEMON_H
#define FIRE_POKEMON_H

#include "Pokemon.h"

class FirePokemon : public Pokemon
{
public:
    FirePokemon(int level = 1);
    FirePokemon(std::string name, PokeType type, int level, int experience, int maxHealth, int currentHealth, int maxMagic, int currentMagic, int baseAttack, int magicRegen, int defense, double evasionRate, double criticalRate, int criticalTurns);

    void useSkill(std::shared_ptr<Pokemon> target) override;

        static std::shared_ptr<FirePokemon> fromJson(const nlohmann::json &j);

    int criticalTurns; // Specific to FirePokemon
};

#endif // FIRE_POKEMON_H