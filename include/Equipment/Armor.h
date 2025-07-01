#pragma once

#include "BaseEquipment.h"

class Armor : public BaseEquipment
{
public:
    int MaxHpBonus;
    float FleeRateBonus;
    Armor() = default;
    Armor(std::string name, int maxHpBonus, float fleeRateBonus)
            : BaseEquipment(name, EquipType::Armor)
    {
        MaxHpBonus = maxHpBonus;
        FleeRateBonus = fleeRateBonus;
    }

    void ShowInfo() override;

    void ApplyEffect() override;

    void RemoveEffect() override;

    void to_json(json& j) const override;
    friend void from_json(const json& j, Armor& p);
};

inline void to_json(json& j, const Armor& a) {
    a.to_json(j);
    j["MaxHpBonus"] = a.MaxHpBonus;
    j["FleeRateBonus"] = a.FleeRateBonus;
}

inline void from_json(const json& j, Armor& a) {
    from_json(j, static_cast<BaseEquipment&>(a));
    j.at("MaxHpBonus").get_to(a.MaxHpBonus);
    j.at("FleeRateBonus").get_to(a.FleeRateBonus);
}

