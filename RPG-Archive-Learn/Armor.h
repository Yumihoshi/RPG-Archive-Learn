#pragma once

#include "BaseEquipment.h"

class Armor : public BaseEquipment
{
public:
    int MaxHpBonus;
    float FleeRateBonus;

    Armor(std::string name, int maxHpBonus, float fleeRateBonus) : BaseEquipment(name)
    {
        MaxHpBonus = maxHpBonus;
        FleeRateBonus = fleeRateBonus;
    }

    void ShowInfo() override;
};

