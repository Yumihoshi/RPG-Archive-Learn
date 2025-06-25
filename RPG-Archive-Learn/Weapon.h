#pragma once

#include "BaseEquipment.h"

class Weapon : public BaseEquipment
{
public:
    int AttackBonus;
    int MaxMpBonus;
    float CritRateBonus;

    Weapon(std::string name, int attackBonus, int maxMpBonus, float critRateBonus) : BaseEquipment(name)
    {
        AttackBonus = attackBonus;
        MaxMpBonus = maxMpBonus;
        CritRateBonus = critRateBonus;
    }

    void ShowInfo() override;
};
