#include "../../include/Poke/GrassPokemon.h"
#include <iostream>

GrassPokemon::GrassPokemon(int level) :
        Pokemon(GRASS, level)
{
}

GrassPokemon::GrassPokemon(std::string name, PokeType type, int level,
                           int experience, int maxHealth, int currentHealth,
                           int maxMagic, int currentMagic, int baseAttack,
                           int magicRegen, int defense, double evasionRate,
                           double criticalRate) :
        Pokemon(name, type, level, experience, maxHealth, currentHealth,
                maxMagic, currentMagic, baseAttack, magicRegen, defense,
                evasionRate, criticalRate)
{
}

void GrassPokemon::useSkill(std::shared_ptr<Pokemon> target)
{
    if (currentMagic >= 10)
    {
        currentMagic -= 10;
        std::cout << name << " 释放了光合作用！" << std::endl;
        int healAmount = 10;
        heal(healAmount);
        std::cout << name << " 恢复了 " << healAmount << " 点生命值！"
                  << std::endl;
    }
    else
    {
        std::cout << name << " 魔法值不足，无法释放技能！" << std::endl;
    }
}

std::shared_ptr<GrassPokemon> GrassPokemon::fromJson(const nlohmann::json &j)
{
    return std::make_shared<GrassPokemon>(j["name"].get<std::string>(),
                                          static_cast<Pokemon::PokeType>(j["type"]),
                                          j["level"].get<int>(),
                                          j["experience"].get<int>(),
                                          j["maxHealth"].get<int>(),
                                          j["currentHealth"].get<int>(),
                                          j["maxMagic"].get<int>(),
                                          j["currentMagic"].get<int>(),
                                          j["baseAttack"].get<int>(),
                                          j["magicRegen"].get<int>(),
                                          j["defense"].get<int>(),
                                          j["evasionRate"].get<double>(),
                                          j["criticalRate"].get<double>());
}
