#ifndef GRASS_POKEMON_H
#define GRASS_POKEMON_H

#include "Pokemon.h"

class GrassPokemon : public Pokemon
{
public:
    GrassPokemon(int level = 1);

    void useSkill(std::shared_ptr<Pokemon> target) override;

    // 序列化用
    GrassPokemon(std::string name, PokeType type, int level, int experience,
                 int maxHealth, int currentHealth, int maxMagic,
                 int currentMagic, int baseAttack, int magicRegen, int defense,
                 double evasionRate, double criticalRate);

    static std::shared_ptr<GrassPokemon> fromJson(const nlohmann::json &j);
};

#endif // GRASS_POKEMON_H
