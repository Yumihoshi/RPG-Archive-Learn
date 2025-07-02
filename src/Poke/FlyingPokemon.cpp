#include "../../include/Poke/FlyingPokemon.h"
#include <iostream>

FlyingPokemon::FlyingPokemon(int level) :
        Pokemon(FLYING, level)
{
}

FlyingPokemon::FlyingPokemon(std::string name, PokeType type, int level,
                             int experience, int maxHealth, int currentHealth,
                             int maxMagic, int currentMagic, int baseAttack,
                             int magicRegen, int defense, double evasionRate,
                             double criticalRate) :
        Pokemon(name, type, level, experience, maxHealth, currentHealth,
                maxMagic, currentMagic, baseAttack, magicRegen, defense,
                evasionRate, criticalRate)
{
}

void FlyingPokemon::useSkill(std::shared_ptr<Pokemon> target)
{
    if (currentMagic >= 10)
    {
        currentMagic -= 10;
        std::cout << name << " 释放了顺风！" << std::endl;
        evasionRate += 0.1;
        std::cout << name << " 的闪避率增加了0.1！" << std::endl;
    }
    else
    {
        std::cout << name << " 魔法值不足，无法释放技能！" << std::endl;
    }
}

std::shared_ptr<FlyingPokemon> FlyingPokemon::fromJson(const nlohmann::json &j)
{
    return std::make_shared<FlyingPokemon>(j["name"].get<std::string>(),
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
