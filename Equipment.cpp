#include "Equipment.h"
#include "Pokemon.h"
#include <iostream>
#include <nlohmann/json.hpp>

// Base Equipment class implementation
Equipment::Equipment(std::string name, Type type) :
    name(name),
    type(type) {}

// Accessory class implementation
Accessory::Accessory(std::string name, int attackBonus, int magicBonus, double criticalRateBonus) :
    Equipment(name, ACCESSORY),
    attackBonus(attackBonus),
    magicBonus(magicBonus),
    criticalRateBonus(criticalRateBonus) {}

void Accessory::applyEffect(Pokemon* pokemon) {
    pokemon->baseAttack += attackBonus;
    pokemon->maxMagic += magicBonus;
    pokemon->currentMagic += magicBonus; // Also increase current magic when max magic increases
    pokemon->criticalRate += criticalRateBonus;
}

void Accessory::removeEffect(Pokemon* pokemon) {
    pokemon->baseAttack -= attackBonus;
    pokemon->maxMagic -= magicBonus;
    pokemon->currentMagic = std::min(pokemon->currentMagic, pokemon->maxMagic); // Adjust current magic if it exceeds new max
    pokemon->criticalRate -= criticalRateBonus;
}

void Accessory::displayStats() const {
    std::cout << "饰品名称: " << name << std::endl;
    std::cout << "攻击加成: " << attackBonus << std::endl;
    std::cout << "魔法值加成: " << magicBonus << std::endl;
    std::cout << "暴击率加成: " << criticalRateBonus << std::endl;
}

nlohmann::json Accessory::toJson() const {
    nlohmann::json j;
    j["name"] = name;
    j["attackBonus"] = attackBonus;
    j["magicBonus"] = magicBonus;
    j["criticalRateBonus"] = criticalRateBonus;
    return j;
}

Accessory* Accessory::fromJson(const nlohmann::json& j) {
    return new Accessory(j["name"], j["attackBonus"], j["magicBonus"], j["criticalRateBonus"]);
}

Accessory::Accessory(const Accessory& other)
    : Equipment(other.name, ACCESSORY),
      attackBonus(other.attackBonus),
      magicBonus(other.magicBonus),
      criticalRateBonus(other.criticalRateBonus) {}

Accessory& Accessory::operator=(const Accessory& other) {
    if (this == &other) {
        return *this;
    }
    name = other.name;
    attackBonus = other.attackBonus;
    magicBonus = other.magicBonus;
    criticalRateBonus = other.criticalRateBonus;
    return *this;
}

// Armor class implementation
Armor::Armor(std::string name, int healthBonus, double evasionRateBonus) :
    Equipment(name, ARMOR),
    healthBonus(healthBonus),
    evasionRateBonus(evasionRateBonus) {}

void Armor::applyEffect(Pokemon* pokemon) {
    pokemon->maxHealth += healthBonus;
    pokemon->currentHealth += healthBonus; // Also increase current health when max health increases
    pokemon->evasionRate += evasionRateBonus;
}

void Armor::removeEffect(Pokemon* pokemon) {
    pokemon->maxHealth -= healthBonus;
    pokemon->currentHealth = std::min(pokemon->currentHealth, pokemon->maxHealth); // Adjust current health if it exceeds new max
    pokemon->evasionRate -= evasionRateBonus;
}

void Armor::displayStats() const {
    std::cout << "防具名称: " << name << std::endl;
    std::cout << "生命值加成: " << healthBonus << std::endl;
    std::cout << "闪避率加成: " << evasionRateBonus << std::endl;
}

nlohmann::json Armor::toJson() const {
    nlohmann::json j;
    j["name"] = name;
    j["healthBonus"] = healthBonus;
    j["evasionRateBonus"] = evasionRateBonus;
    return j;
}

Armor* Armor::fromJson(const nlohmann::json& j) {
    return new Armor(j["name"], j["healthBonus"], j["evasionRateBonus"]);
}

Armor::Armor(const Armor& other)
    : Equipment(other.name, ARMOR),
      healthBonus(other.healthBonus),
      evasionRateBonus(other.evasionRateBonus) {}

Armor& Armor::operator=(const Armor& other) {
    if (this == &other) {
        return *this;
    }
    name = other.name;
    healthBonus = other.healthBonus;
    evasionRateBonus = other.evasionRateBonus;
    return *this;
}
