#pragma once

#include "Skill.h"
#include "../../Managers/LogManager.h"

class NormalAttackSkill : public Skill
{
public:
    NormalAttackSkill() : Skill("普通攻击", "对敌人造成物理伤害", 0) {}

    void Use(const std::shared_ptr<BasePokeModel>& user, const std::shared_ptr<BasePokeModel>& target) override
    {
        LogManager::PrintByChar(user->GetName() + " 对 " + target->GetName() + " 使用了普通攻击！\n");
        float critRateBonus = 0.0f;
        if (user->GetDecoration()) {
            critRateBonus = user->GetDecoration()->CritRateBonus;
        }
        int damage = user->CalculateDamage(critRateBonus);
        target->TakeDamage(damage);
    }
};
