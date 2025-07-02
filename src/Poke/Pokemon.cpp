#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "../../include/Poke/Pokemon.h"
#include "../../include/Equip/Equipment.h"
#include "../../include/Equip/Accessory.h"
#include "../../include/Equip/Armor.h"

// 宝可梦构造函数
Pokemon::Pokemon(PokeType type, int level) :
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

// 用于JSON序列化的构造函数
Pokemon::Pokemon(std::string name, PokeType type, int level, int experience,
                 int maxHealth, int currentHealth, int maxMagic,
                 int currentMagic, int baseAttack, int magicRegen, int defense,
                 double evasionRate, double criticalRate) :
        name(name),
        type(type),
        level(level),
        experience(experience),
        maxHealth(maxHealth),
        currentHealth(currentHealth),
        maxMagic(maxMagic),
        currentMagic(currentMagic),
        baseAttack(baseAttack),
        magicRegen(magicRegen),
        defense(defense),
        evasionRate(evasionRate),
        criticalRate(criticalRate),
        accessory(nullptr),
        armor(nullptr)
{
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
        statusEffects(other.statusEffects),
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
    statusEffects = other.statusEffects;

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

void Pokemon::applyStatusEffect(const std::string &effectName, int duration)
{
    statusEffects[effectName] = duration;
}

void Pokemon::removeStatusEffect(const std::string &effectName)
{
    statusEffects.erase(effectName);
}

bool Pokemon::hasStatusEffect(const std::string &effectName) const
{
    return statusEffects.count(effectName) > 0;
}

void Pokemon::decrementStatusEffects()
{
    std::vector<std::string> effectsToRemove;
    for (auto &pair: statusEffects)
    {
        pair.second--;
        if (pair.second <= 0)
        {
            effectsToRemove.push_back(pair.first);
        }
    }
    for (const auto &effect: effectsToRemove)
    {
        removeStatusEffect(effect);
    }
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
    j["statusEffects"] = statusEffects;
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


// 根据宝可梦属性初始化基础属性
void Pokemon::initializeStats(PokeType type)
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

// 应用随机波动
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

// 获取随机名字
std::string Pokemon::getRandomName(PokeType type)
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

// 应用经验和升级
void Pokemon::gainExperience(int exp)
{
    experience += exp;
    while (experience >= 100 && level < 10)
    {
        experience -= 100;
        level++;
        std::cout << name << "升级了！现在是等级 " << level << "！" << std::endl;
        // 升级提高属性
        maxHealth += 10;
        maxMagic += 5;
        baseAttack += 2;
        defense += 1;
        currentHealth = maxHealth; // 升级回复生命值
        currentMagic = maxMagic;   // 升级回复魔法值
    }
}

// 处理受到伤害
void Pokemon::takeDamage(int damage)
{
    currentHealth -= damage;
    if (currentHealth < 0)
    {
        currentHealth = 0;
    }
}

// 回血
void Pokemon::heal(int amount)
{
    currentHealth += amount;
    if (currentHealth > maxHealth)
    {
        currentHealth = maxHealth;
    }
}

// 回魔
void Pokemon::restoreMagic(int amount)
{
    currentMagic += amount;
    if (currentMagic > maxMagic)
    {
        currentMagic = maxMagic;
    }
    std::cout << name << "恢复了" << amount << "点魔法。" << std::endl;
}

// 是否死亡
bool Pokemon::isFainted() const
{
    return currentHealth <= 0;
}

// 显示状态信息
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
    std::cout << "饰品: " << (accessory ? accessory->name : "无") << std::endl;
    std::cout << "防具: " << (armor ? armor->name : "无") << std::endl;
    std::cout << "--------------------" << std::endl;
}
