#include "../../include/Poke/GhostPokemon.h"
#include <iostream>

GhostPokemon::GhostPokemon(int level) :
    Pokemon(GHOST, level)
{
}

GhostPokemon::GhostPokemon(std::string name, PokeType type, int level, int experience, int maxHealth, int currentHealth, int maxMagic, int currentMagic, int baseAttack, int magicRegen, int defense, double evasionRate, double criticalRate) :
    Pokemon(name, type, level, experience, maxHealth, currentHealth, maxMagic, currentMagic, baseAttack, magicRegen, defense, evasionRate, criticalRate)
{
}

void GhostPokemon::useSkill(std::shared_ptr<Pokemon> target)
{
    if (currentMagic >= 10)
    {
        currentMagic -= 10;
        std::cout << name << " 释放了暗影突袭！" << std::endl;
        // Example skill effect: deals damage and has a chance to stun (requires status effect system)
        int damage = baseAttack * 1.8; // 180% of base attack
        target->takeDamage(damage);
        std::cout << name << " 对 " << target->name << " 造成了 " << damage << " 点伤害！" << std::endl;
        std::cout << target->name << " 感到一阵恐惧！" << std::endl;
    }
    else
    {
        std::cout << name << " 魔法值不足，无法释放技能！" << std::endl;
    }
}

std::shared_ptr<GhostPokemon> GhostPokemon::fromJson(const nlohmann::json &j)
{
    return std::make_shared<GhostPokemon>(j["name"].get<std::string>(),
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