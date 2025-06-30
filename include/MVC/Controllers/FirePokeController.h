#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../Models/FirePokeModel.h"
#include "../Views/FirePokeView.h"

class FirePokeController : public BasePokeController
{
public:
    explicit FirePokeController(std::shared_ptr<FirePokeModel> model) : BasePokeController(std::move(model))
    {
    }

    // 攻击
    void Attack(const std::shared_ptr<BasePokeModel> &other) override
    {
        if (!other->IsAlive()) return;
        // 计算攻击方伤害
        int damage = ModelPtr->GetDamage();
        LogManager::PrintByChar(
                ModelPtr->GetName() + "向" + other->GetName() + "发动了攻击，");
        auto m = std::dynamic_pointer_cast<FirePokeModel>(ModelPtr);
        // 必定暴击
        if (m->CritCount > 0)
        {
            m->CritCount--;
            damage *= 1.5f;
            LogManager::PrintByChar("且发生了");
            LogManager::PrintByChar("暴击", LogColor::Red);
            LogManager::PrintByChar("！");
        }
        else if (m->CritCount <= 0 && CheckCrit())
        {
            damage *= 1.5f;
            LogManager::PrintByChar("且发生了");
            LogManager::PrintByChar("暴击", LogColor::Red);
            LogManager::PrintByChar("！");
        }
        LogManager::PrintByChar("伤害值为" + std::to_string(damage) + "\n");
        other->TakeDamage(damage);
    }
};

