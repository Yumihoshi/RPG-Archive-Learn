#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <map>
#include <random>
#include <ctime>
#include <nlohmann/json.hpp> // For JSON serialization/deserialization

// Forward declarations for Equipment classes
class Accessory;
class Armor;

class Pokemon {
public:
    // JSON serialization/deserialization
    nlohmann::json toJson() const;
    static Pokemon fromJson(const nlohmann::json& j);
public:
    enum Type { FIRE, GRASS, ICE, FLYING, GHOST };

    Pokemon(Type type, int level = 1);

    // Basic attributes
    std::string name;
    Type type;
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

    // Equipment slots
    Accessory* accessory;
    Armor* armor;

    void gainExperience(int exp);
    void takeDamage(int damage);
    void heal(int amount);
    void restoreMagic(int amount);
    bool isFainted() const;
    void displayStats() const;

    // Destructor, Copy Constructor, Copy Assignment Operator for proper memory management
    ~Pokemon();
    Pokemon(const Pokemon& other);
    Pokemon& operator=(const Pokemon& other);

private:
    void initializeStats(Type type);
    void applyRandomFluctuation();
    std::string getRandomName(Type type);
};

#endif // POKEMON_H
