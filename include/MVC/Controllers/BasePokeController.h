#pragma once

#include <iostream>
#include <random>
#include <string>
#include <utility>
#include "../Models/BasePokeModel.h"
#include "../Views/BasePokeView.h"
#include "../Views/FirePokeView.h"
#include "../Views/GhostPokeView.h"
#include "../Views/GrassPokeView.h"
#include "../Views/IcePokeView.h"
#include "../Views/FlyPokeView.h"
#include "../../Managers/LogManager.h"

class BasePokeController
{
public:
    std::shared_ptr<BasePokeModel> ModelPtr;
    std::shared_ptr<BasePokeView> ViewPtr;

    explicit BasePokeController(std::shared_ptr<BasePokeModel> model)
    {
        ModelPtr = std::move(model);
        InitView();
        _gen = std::mt19937(_rd());
    }

    // 攻击
    virtual void Attack(const std::shared_ptr<BasePokeModel> &other)
    {
        if (!other->IsAlive()) return;
        // 计算攻击方伤害
        int damage = ModelPtr->GetDamage();
        LogManager::PrintByChar(
                ModelPtr->GetName() + "向" + other->GetName() + "发动了攻击，");
        if (CheckCrit())
        {
            damage *= 1.5f;
            LogManager::PrintByChar("且发生了");
            LogManager::PrintByChar("暴击", LogColor::Red);
            LogManager::PrintByChar("！");
        }
        LogManager::PrintByChar("伤害值为" + std::to_string(damage) + "\n");
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

private:
    // 初始化视图
    void InitView()
    {
        switch (ModelPtr->GetElement())
        {
            case ElementType::None:
                break;
            case ElementType::Fire:
            {
                FirePokeView firePokeView(
                        std::dynamic_pointer_cast<FirePokeModel>(ModelPtr));
                ViewPtr = std::make_shared<FirePokeView>(firePokeView);
                break;
            }
            case ElementType::Ice:
            {
                IcePokeView icePokeView(
                        std::dynamic_pointer_cast<IcePokeModel>(ModelPtr));
                ViewPtr = std::make_shared<IcePokeView>(icePokeView);
                break;
            }
            case ElementType::Grass:
            {
                GrassPokeView grassPokeView(
                        std::dynamic_pointer_cast<GrassPokeModel>(ModelPtr));
                ViewPtr = std::make_shared<GrassPokeView>(grassPokeView);
                break;
            }
            case ElementType::Fly:
            {
                FlyPokeView flyPokeView(
                        std::dynamic_pointer_cast<FlyPokeModel>(ModelPtr));
                ViewPtr = std::make_shared<FlyPokeView>(flyPokeView);
                break;
            }
            case ElementType::Ghost:
            {
                GhostPokeView ghostPokeView(
                        std::dynamic_pointer_cast<GhostPokeModel>(ModelPtr));
                ViewPtr = std::make_shared<GhostPokeView>(ghostPokeView);
                break;
            }
        }
    }
};

