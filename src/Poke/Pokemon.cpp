#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "../../include/Poke/Pokemon.h"
#include "../../include/Equip/Equipment.h"
#include "../../include/Equip/Accessory.h"
#include "../../include/Equip/Armor.h"

// Constructor
Pokemon::Pokemon(Type type, int level) :
        type(type),
        level(level),
        experience(0),
        currentHealth(0),
        currentMagic(0),
        accessory(nullptr),
        armor(nullptr)
{
    initializeStats(type);
    applyRandomFluctuation();
    name = getRandomName(type);
    currentHealth = maxHealth;
    currentMagic = maxMagic;
}

Pokemon::Pokemon(const Pokemon &other) :
        name(other.name),
        type(other.type),
        level(other.level),
        experience(other.experience),
        maxHealth(other.maxHealth),
        currentHealth(other.currentHealth),
        maxMagic(other.maxMagic),
        currentMagic(other.currentMagic),
        baseAttack(other.baseAttack),
        magicRegen(other.magicRegen),
        defense(other.defense),
        evasionRate(other.evasionRate),
        criticalRate(other.criticalRate),
        accessory(nullptr),
        armor(nullptr)
{
    if (other.accessory)
    {
        accessory = std::make_shared<Accessory>(*other.accessory);
    }
    if (other.armor)
    {
        armor = std::make_shared<Armor>(*other.armor);
    }
}

Pokemon &Pokemon::operator=(const Pokemon &other)
{
    if (this == &other)
    {
        return *this;
    }

    // Copy data members
    name = other.name;
    type = other.type;
    level = other.level;
    experience = other.experience;
    maxHealth = other.maxHealth;
    currentHealth = other.currentHealth;
    maxMagic = other.maxMagic;
    currentMagic = other.currentMagic;
    baseAttack = other.baseAttack;
    magicRegen = other.magicRegen;
    defense = other.defense;
    evasionRate = other.evasionRate;
    criticalRate = other.criticalRate;

    // Deep copy equipment
    accessory = nullptr;
    armor = nullptr;
    if (other.accessory)
    {
        accessory = std::make_shared<Accessory>(*other.accessory);
    }
    if (other.armor)
    {
        armor = std::make_shared<Armor>(*other.armor);
    }

    return *this;
}

nlohmann::json Pokemon::toJson() const
{
    nlohmann::json j;
    j["name"] = name;
    j["type"] = type;
    j["level"] = level;
    j["experience"] = experience;
    j["maxHealth"] = maxHealth;
    j["currentHealth"] = currentHealth;
    j["maxMagic"] = maxMagic;
    j["currentMagic"] = currentMagic;
    j["baseAttack"] = baseAttack;
    j["magicRegen"] = magicRegen;
    j["defense"] = defense;
    j["evasionRate"] = evasionRate;
    j["criticalRate"] = criticalRate;
    if (accessory)
    {
        j["accessory"] = accessory->toJson();
    }
    if (armor)
    {
        j["armor"] = armor->toJson();
    }
    return j;
}

Pokemon Pokemon::fromJson(const nlohmann::json &j)
{
    Pokemon p(static_cast<Pokemon::Type>(j["type"]), j["level"]);
    p.name = j["name"];
    p.experience = j["experience"];
    p.maxHealth = j["maxHealth"];
    p.currentHealth = j["currentHealth"];
    p.maxMagic = j["maxMagic"];
    p.currentMagic = j["currentMagic"];
    p.baseAttack = j["baseAttack"];
    p.magicRegen = j["magicRegen"];
    p.defense = j["defense"];
    p.evasionRate = j["evasionRate"];
    p.criticalRate = j["criticalRate"];
    if (j.contains("accessory"))
    {
        p.accessory = Accessory::fromJson(j["accessory"]);
    }
    if (j.contains("armor"))
    {
        p.armor = Armor::fromJson(j["armor"]);
    }
    return p;
}

// Initialize base stats based on Pokemon type
void Pokemon::initializeStats(Type type)
{
    switch (type)
    {
        case FIRE:
            maxHealth = 120;
            maxMagic = 30;
            baseAttack = 8;
            magicRegen = 5;
            defense = 0;
            evasionRate = 0.1;
            criticalRate = 0.2;
            break;
        case GRASS:
            maxHealth = 100;
            maxMagic = 65;
            baseAttack = 10;
            magicRegen = 5;
            defense = 0;
            evasionRate = 0.1;
            criticalRate = 0.15;
            break;
        case ICE:
            maxHealth = 100;
            maxMagic = 50;
            baseAttack = 10;
            magicRegen = 10;
            defense = 5;
            evasionRate = 0.1;
            criticalRate = 0.15;
            break;
        case FLYING:
            maxHealth = 50;
            maxMagic = 50;
            baseAttack = 30;
            magicRegen = 5;
            defense = 0;
            evasionRate = 0.1;
            criticalRate = 0.15;
            break;
        case GHOST:
            maxHealth = 80;
            maxMagic = 50;
            baseAttack = 10;
            magicRegen = 5;
            defense = 0;
            evasionRate = 0.3;
            criticalRate = 0.15;
            break;
    }
}

// Apply random fluctuation to stats
void Pokemon::applyRandomFluctuation()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.9, 1.1);

    maxHealth = static_cast<int>(maxHealth * distrib(gen));
    maxMagic = static_cast<int>(maxMagic * distrib(gen));
    baseAttack = static_cast<int>(baseAttack * distrib(gen));
    magicRegen = static_cast<int>(magicRegen * distrib(gen));
    defense = static_cast<int>(defense * distrib(gen));
    evasionRate = evasionRate * distrib(gen);
    criticalRate = criticalRate * distrib(gen);
}

// Get a random name based on Pokemon type
std::string Pokemon::getRandomName(Type type)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::string> names;

    switch (type)
    {
        case FIRE:
            names = {"小火龙", "烈焰马", "暖暖猪", "火狐狸"};
            break;
        case GRASS:
            names = {"草苗龟", "樱花宝", "青藤蛇", "坐骑山羊"};
            break;
        case ICE:
            names = {"迷你冰", "雪童子", "冰伊布", "喷嚏熊"};
            break;
        case FLYING:
            names = {"大比鸟", "飞天螳螂", "长翅鸥", "彩粉蝶"};
            break;
        case GHOST:
            names = {"耿鬼", "魔灵珊瑚", "灵幽马", "黑夜魔灵"};
            break;
    }
    std::uniform_int_distribution<> distrib(0, names.size() - 1);
    return names[distrib(gen)];
}

// Handle experience gain and leveling up
void Pokemon::gainExperience(int exp)
{
    experience += exp;
    while (experience >= 100 && level < 10)
    {
        experience -= 100;
        level++;
        std::cout << name << "升级了！现在是等级 " << level << "！" << std::endl;
        // Increase stats on level up (example, can be more sophisticated)
        maxHealth += 10;
        maxMagic += 5;
        baseAttack += 2;
        defense += 1;
        currentHealth = maxHealth; // Fully heal on level up
        currentMagic = maxMagic;   // Fully restore magic on level up
    }
}

// Handle taking damage
void Pokemon::takeDamage(int damage)
{
    currentHealth -= damage;
    if (currentHealth < 0)
    {
        currentHealth = 0;
    }
}

// Handle healing
void Pokemon::heal(int amount)
{
    currentHealth += amount;
    if (currentHealth > maxHealth)
    {
        currentHealth = maxHealth;
    }
}

// Handle magic restoration
void Pokemon::restoreMagic(int amount)
{
    currentMagic += amount;
    if (currentMagic > maxMagic)
    {
        currentMagic = maxMagic;
    }
}

// Check if the Pokemon is fainted
bool Pokemon::isFainted() const
{
    return currentHealth <= 0;
}

// Display Pokemon stats
void Pokemon::displayStats() const
{
    std::cout << "--------------------" << std::endl;
    std::cout << "名字: " << name << std::endl;
    std::cout << "类型: ";
    switch (type)
    {
        case FIRE:
            std::cout << "火";
            break;
        case GRASS:
            std::cout << "草";
            break;
        case ICE:
            std::cout << "冰";
            break;
        case FLYING:
            std::cout << "飞行";
            break;
        case GHOST:
            std::cout << "幽灵";
            break;
    }
    std::cout << std::endl;
    std::cout << "等级: " << level << std::endl;
    std::cout << "经验: " << experience << std::endl;
    std::cout << "生命值: " << currentHealth << "/" << maxHealth << std::endl;
    std::cout << "魔法值: " << currentMagic << "/" << maxMagic << std::endl;
    std::cout << "基础攻击: " << baseAttack << std::endl;
    std::cout << "魔法回复: " << magicRegen << std::endl;
    std::cout << "防御力: " << defense << std::endl;
    std::cout << "闪避率: " << evasionRate << std::endl;
    std::cout << "暴击率: " << criticalRate << std::endl;
    std::cout << "饰品: " << (accessory ? "已装备" : "无") << std::endl;
    std::cout << "防具: " << (armor ? "已装备" : "无") << std::endl;
    std::cout << "--------------------" << std::endl;
}
