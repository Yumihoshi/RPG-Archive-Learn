/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午1:41
* @version: 1.0
* @description: 
*******************************************************************************/
#include <iostream>
#include "../../include/Equip/Armor.h"
#include "../../include/Poke/Pokemon.h"

// 防具构造函数
Armor::Armor(std::string name, int healthBonus, double evasionRateBonus) :
        Equipment(name, ARMOR),
        healthBonus(healthBonus),
        evasionRateBonus(evasionRateBonus)
{}

void Armor::applyEffect(std::shared_ptr<Pokemon> pokemon)
{
    pokemon->maxHealth += healthBonus;
    pokemon->currentHealth += healthBonus;
    pokemon->evasionRate += evasionRateBonus;
}

void Armor::removeEffect(std::shared_ptr<Pokemon> pokemon)
{
    pokemon->maxHealth -= healthBonus;
    pokemon->currentHealth = std::min(pokemon->currentHealth,
                                      pokemon->maxHealth);
    pokemon->evasionRate -= evasionRateBonus;
}

void Armor::displayStats() const
{
    std::cout << "防具名称: " << name << std::endl;
    std::cout << "生命值加成: " << healthBonus << std::endl;
    std::cout << "闪避率加成: " << evasionRateBonus << std::endl;
}

nlohmann::json Armor::toJson() const
{
    nlohmann::json j;
    j["name"] = name;
    j["healthBonus"] = healthBonus;
    j["evasionRateBonus"] = evasionRateBonus;
    return j;
}

std::shared_ptr<Armor> Armor::fromJson(const nlohmann::json &j)
{
    return std::make_shared<Armor>(j["name"].get<std::string>(),
                                   j["healthBonus"].get<int>(),
                                   j["evasionRateBonus"].get<double>());
}

Armor::Armor(const Armor &other)
        : Equipment(other.name, ARMOR),
          healthBonus(other.healthBonus),
          evasionRateBonus(other.evasionRateBonus)
{}

Armor &Armor::operator=(const Armor &other)
{
    if (this == &other)
    {
        return *this;
    }
    name = other.name;
    healthBonus = other.healthBonus;
    evasionRateBonus = other.evasionRateBonus;
    return *this;
}
