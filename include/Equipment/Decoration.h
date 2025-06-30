#pragma once

#include "BaseEquipment.h"

class Decoration : public BaseEquipment
{
public:
    int AttackBonus;
    int MaxMpBonus;
    float CritRateBonus;
    float FleeRateBonus;

    Decoration(std::string name, int attackBonus, int maxMpBonus, float critRateBonus, float fleeRateBonus) : BaseEquipment(name)
    {
        AttackBonus = attackBonus;
        MaxMpBonus = maxMpBonus;
        CritRateBonus = critRateBonus;
        FleeRateBonus = fleeRateBonus;
    }

    void ShowInfo() override;
    void ApplyEffect() override;
    void RemoveEffect() override;
};
