#pragma once

#include "BaseEquipment.h"

class Decoration : public BaseEquipment
{
public:
    int AttackBonus;
    int MaxMpBonus;
    float CritRateBonus;
    float FleeRateBonus;

    Decoration() = default;

    Decoration(std::string name, int attackBonus, int maxMpBonus,
               float critRateBonus, float fleeRateBonus) : BaseEquipment(name,
                                                                         EquipType::Decoration)
    {
        AttackBonus = attackBonus;
        MaxMpBonus = maxMpBonus;
        CritRateBonus = critRateBonus;
        FleeRateBonus = fleeRateBonus;
    }

    void ShowInfo() override;

    void ApplyEffect() override;

    void RemoveEffect() override;

    void to_json(json& j) const override;
    friend void from_json(const json& j, Decoration& p);
};

inline void to_json(json& j, const Decoration& d) {
    d.to_json(j);
    j["AttackBonus"] = d.AttackBonus;
    j["MaxMpBonus"] = d.MaxMpBonus;
    j["CritRateBonus"] = d.CritRateBonus;
    j["FleeRateBonus"] = d.FleeRateBonus;
}

inline void from_json(const json& j, Decoration& d) {
    from_json(j, static_cast<BaseEquipment&>(d));
    j.at("AttackBonus").get_to(d.AttackBonus);
    j.at("MaxMpBonus").get_to(d.MaxMpBonus);
    j.at("CritRateBonus").get_to(d.CritRateBonus);
    j.at("FleeRateBonus").get_to(d.FleeRateBonus);
}
