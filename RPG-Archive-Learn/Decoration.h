#pragma once

#include "BaseEquipment.h"

class Decoration : public BaseEquipment
{
public:
    int AttackBonus;
    int MaxMpBonus;
    float CritRateBonus;

    Decoration(std::string name, int attackBonus, int maxMpBonus, float critRateBonus) : BaseEquipment(name)
    {
        AttackBonus = attackBonus;
        MaxMpBonus = maxMpBonus;
        CritRateBonus = critRateBonus;
    }

    void ShowInfo() override;
};
