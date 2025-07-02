#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <nlohmann/json.hpp>

class Pokemon;

class Equipment
{
public:
    enum Type
    {
        ACCESSORY, ARMOR
    };

    Equipment(std::string name, Type type);

    virtual ~Equipment() = default;

    std::string name;
    Type type;

    virtual void applyEffect(Pokemon& pokemon) = 0;

    virtual void removeEffect(Pokemon& pokemon) = 0;

    virtual void displayStats() const = 0;
};

#endif // EQUIPMENT_H
