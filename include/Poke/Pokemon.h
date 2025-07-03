#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <map>
#include <random>
#include <ctime>
#include <nlohmann/json.hpp>

// 前向声明
class Accessory;

class Armor;

class Pokemon
{
public:
    // JSON序列化
    nlohmann::json toJson() const;

public:
    enum PokeType
    {
        FIRE, GRASS, ICE, FLYING, GHOST
    };

protected:
    Pokemon(PokeType type, int level = 1);

    Pokemon(std::string name, PokeType type, int level, int experience,
            int maxHealth, int currentHealth, int maxMagic, int currentMagic,
            int baseAttack, int magicRegen, int defense, double evasionRate,
            double criticalRate);

public:
    std::string name;
    PokeType type;
    int level;
    int experience;
    int maxHealth;
    int currentHealth;
    int maxMagic;
    int currentMagic;
    int baseAttack;
    int magicRegen;
    int defense;
    double evasionRate;
    double criticalRate;

    // 状态效果
    std::map<std::string, int> statusEffects;

    // 装备槽
    std::shared_ptr<Accessory> accessory;
    std::shared_ptr<Armor> armor;

    void gainExperience(int exp);

    void takeDamage(int damage);

    void heal(int amount);

    void restoreMagic(int amount);

    bool isFainted() const;

    void displayStats() const;

    Pokemon(const Pokemon &other);

    Pokemon &operator=(const Pokemon &other);

    void applyStatusEffect(const std::string &effectName, int duration);

    void removeStatusEffect(const std::string &effectName);

    bool hasStatusEffect(const std::string &effectName) const;

    void decrementStatusEffects();

    virtual void useSkill(std::shared_ptr<Pokemon> target) = 0;

private:
    void initializeStats(PokeType type);

    void applyRandomFluctuation();

    std::string getRandomName(PokeType type);
};

#endif // POKEMON_H
