#pragma once

#include <iostream>
#include <random>
#include <string>
#include "../Models/BasePokeModel.h"
#include "../../Managers/LogManager.h"

template<typename T, typename T2>
class BasePokeController
{
public:
    std::shared_ptr<T> ModelPtr;
    std::shared_ptr<T2> ViewPtr;

    BasePokeController(std::shared_ptr<T> model)
    {
        ModelPtr = model;
        ViewPtr = std::make_shared<T2>(model);
        _gen = std::mt19937(_rd());
    }

    // 攻击
    void Attack(std::shared_ptr<BasePokeModel> other)
    {
        if (!other->IsAlive()) return;
        auto& logger = LogManager::GetInstance();
        // 计算攻击方伤害
        int damage = ModelPtr->GetDamage();
        logger.PrintByChar(ModelPtr->GetName() + "向" + other->GetName() + "发动了攻击，");
        if (CheckCrit())
        {
            damage *= 1.5f;
            logger.PrintByChar("且发生了");
            logger.PrintByChar("暴击", LogColor::Red);
            logger.PrintByChar("！");
        }
        logger.PrintByChar("伤害值为" + std::to_string(damage) + "\n");
        other->TakeDamage(damage);
    }

protected:
    std::random_device _rd;
    std::mt19937 _gen;
    // 是否暴击
    bool CheckCrit()
    {
        std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        return distribution(_gen) < ModelPtr->GetCritRate();
    }
};

