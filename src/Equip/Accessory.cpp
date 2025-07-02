/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午1:40
* @version: 1.0
* @description: 
*******************************************************************************/
#include <iostream>
#include "../../include/Equip/Accessory.h"
#include "../../include/Poke/Pokemon.h"

// Accessory class implementation
Accessory::Accessory(std::string name, int attackBonus, int magicBonus,
                     double criticalRateBonus) :
        Equipment(name, ACCESSORY),
        attackBonus(attackBonus),
        magicBonus(magicBonus),
        criticalRateBonus(criticalRateBonus)
{}

void Accessory::applyEffect(Pokemon& pokemon)
{
    pokemon.baseAttack += attackBonus;
    pokemon.maxMagic += magicBonus;
    pokemon.currentMagic += magicBonus; // Also increase current magic when max magic increases
    pokemon.criticalRate += criticalRateBonus;
}

void Accessory::removeEffect(Pokemon& pokemon)
{
    pokemon.baseAttack -= attackBonus;
    pokemon.maxMagic -= magicBonus;
    pokemon.currentMagic = std::min(pokemon.currentMagic,
                                     pokemon.maxMagic); // Adjust current magic if it exceeds new max
    pokemon.criticalRate -= criticalRateBonus;
}

void Accessory::displayStats() const
{
    std::cout << "饰品名称: " << name << std::endl;
    std::cout << "攻击加成: " << attackBonus << std::endl;
    std::cout << "魔法值加成: " << magicBonus << std::endl;
    std::cout << "暴击率加成: " << criticalRateBonus << std::endl;
}

nlohmann::json Accessory::toJson() const
{
    nlohmann::json j;
    j["name"] = name;
    j["attackBonus"] = attackBonus;
    j["magicBonus"] = magicBonus;
    j["criticalRateBonus"] = criticalRateBonus;
    return j;
}

std::shared_ptr<Accessory> Accessory::fromJson(const nlohmann::json &j)
{
    return std::make_shared<Accessory>(
            Accessory(j["name"], j["attackBonus"], j["magicBonus"],
                      j["criticalRateBonus"]));
}

Accessory::Accessory(const Accessory &other)
        : Equipment(other.name, ACCESSORY),
          attackBonus(other.attackBonus),
          magicBonus(other.magicBonus),
          criticalRateBonus(other.criticalRateBonus)
{}

Accessory &Accessory::operator=(const Accessory &other)
{
    if (this == &other)
    {
        return *this;
    }
    name = other.name;
    attackBonus = other.attackBonus;
    magicBonus = other.magicBonus;
    criticalRateBonus = other.criticalRateBonus;
    return *this;
}
