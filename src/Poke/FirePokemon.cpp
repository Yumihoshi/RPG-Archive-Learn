#include "../../include/Poke/FirePokemon.h"
#include "../../include/Equip/Accessory.h"
#include "../../include/Equip/Armor.h"
#include <iostream>

FirePokemon::FirePokemon(int level) :
        Pokemon(FIRE, level),
        criticalTurns(0)
{
}

FirePokemon::FirePokemon(std::string name, PokeType type, int level,
                         int experience, int maxHealth, int currentHealth,
                         int maxMagic, int currentMagic, int baseAttack,
                         int magicRegen, int defense, double evasionRate,
                         double criticalRate, int criticalTurns) :
        Pokemon(name, type, level, experience, maxHealth, currentHealth,
                maxMagic, currentMagic, baseAttack, magicRegen, defense,
                evasionRate, criticalRate),
        criticalTurns(criticalTurns)
{
}

void FirePokemon::useSkill(std::shared_ptr<Pokemon> target)
{
    if (currentMagic >= 10)
    {
        currentMagic -= 10;
        std::cout << name << " 释放了火焰技能！" << std::endl;
        criticalTurns = 3; // Guaranteed critical for 3 turns
        std::cout << name << " 的攻击在接下来的 " << criticalTurns
                  << " 回合内必定暴击！" << std::endl;
    }
    else
    {
        std::cout << name << " 魔法值不足，无法释放技能！" << std::endl;
    }
}

std::shared_ptr<FirePokemon> FirePokemon::fromJson(const nlohmann::json &j)
{
    std::shared_ptr<FirePokemon> pokemon = std::make_shared<FirePokemon>(j["name"].get<std::string>(),
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
                                                                         j["criticalRate"].get<double>(),
                                                                         j["criticalTurns"].get<int>());
    if (j.contains("accessory"))
    {
        pokemon->accessory = Accessory::fromJson(j["accessory"]);
    }
    if (j.contains("armor"))
    {
        pokemon->armor = Armor::fromJson(j["armor"]);
    }
    return pokemon;
}
