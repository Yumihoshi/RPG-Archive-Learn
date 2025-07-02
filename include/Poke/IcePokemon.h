#ifndef ICE_POKEMON_H
#define ICE_POKEMON_H

#include "Pokemon.h"

class IcePokemon : public Pokemon
{
public:
    IcePokemon(int level = 1);

    void useSkill(std::shared_ptr<Pokemon> target) override;

    // For serialization
    IcePokemon(std::string name, PokeType type, int level, int experience, int maxHealth, int currentHealth, int maxMagic, int currentMagic, int baseAttack, int magicRegen, int defense, double evasionRate, double criticalRate);

    static std::shared_ptr<IcePokemon> fromJson(const nlohmann::json &j);
};

#endif // ICE_POKEMON_H