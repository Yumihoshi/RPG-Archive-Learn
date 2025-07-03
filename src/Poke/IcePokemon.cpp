#include "../../include/Poke/IcePokemon.h"
#include "../../include/Equip/Accessory.h"
#include "../../include/Equip/Armor.h"
#include <iostream>

IcePokemon::IcePokemon(int level) :
        Pokemon(ICE, level)
{
}

IcePokemon::IcePokemon(std::string name, PokeType type, int level,
                       int experience, int maxHealth, int currentHealth,
                       int maxMagic, int currentMagic, int baseAttack,
                       int magicRegen, int defense, double evasionRate,
                       double criticalRate) :
        Pokemon(name, type, level, experience, maxHealth, currentHealth,
                maxMagic, currentMagic, baseAttack, magicRegen, defense,
                evasionRate, criticalRate)
{
}

void IcePokemon::useSkill(std::shared_ptr<Pokemon> target)
{
    if (currentMagic >= 10)
    {
        currentMagic -= 10;
        std::cout << name << " 释放了冰冻之风！" << std::endl;
        // Example skill effect: deals damage and reduces target's attack
        int damage = baseAttack * 1.5; // 150% of base attack
        target->takeDamage(damage);
        std::cout << name << " 对 " << target->name << " 造成了 " << damage
                  << " 点伤害！" << std::endl;
        target->applyStatusEffect("Frozen", 3);
        std::cout << target->name << " 被冻结了3回合！" << std::endl;
    }
    else
    {
        std::cout << name << " 魔法值不足，无法释放技能！" << std::endl;
    }
}

std::shared_ptr<IcePokemon> IcePokemon::fromJson(const nlohmann::json &j)
{
    std::shared_ptr<IcePokemon> pokemon = std::make_shared<IcePokemon>(j["name"].get<std::string>(),
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
