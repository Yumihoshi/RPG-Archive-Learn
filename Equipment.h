#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <nlohmann/json.hpp>

class Pokemon;

class Equipment {
public:
    enum Type { ACCESSORY, ARMOR };

    Equipment(std::string name, Type type);
    virtual ~Equipment() = default;

    std::string name;
    Type type;

    virtual void applyEffect(Pokemon* pokemon) = 0;
    virtual void removeEffect(Pokemon* pokemon) = 0;
    virtual void displayStats() const = 0;
};

class Accessory : public Equipment {
public:
    Accessory(std::string name, int attackBonus, int magicBonus, double criticalRateBonus);

    int attackBonus;
    int magicBonus;
    double criticalRateBonus;

    void applyEffect(Pokemon* pokemon) override;
    void removeEffect(Pokemon* pokemon) override;
    void displayStats() const override;

    nlohmann::json toJson() const;
    static Accessory* fromJson(const nlohmann::json& j);

    // Copy constructor and assignment operator
    Accessory(const Accessory& other);
    Accessory& operator=(const Accessory& other);
};

class Armor : public Equipment {
public:
    Armor(std::string name, int healthBonus, double evasionRateBonus);

    int healthBonus;
    double evasionRateBonus;

    void applyEffect(Pokemon* pokemon) override;
    void removeEffect(Pokemon* pokemon) override;
    void displayStats() const override;

    nlohmann::json toJson() const;
    static Armor* fromJson(const nlohmann::json& j);

    // Copy constructor and assignment operator
    Armor(const Armor& other);
    Armor& operator=(const Armor& other);
};

#endif // EQUIPMENT_H
