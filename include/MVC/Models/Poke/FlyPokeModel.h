#pragma once
#include <utility>

#include "BasePokeModel.h"
class FlyPokeModel :public BasePokeModel
{
public:
    FlyPokeModel(std::string name, CampType camp) :BasePokeModel(std::move(name), ElementType::Fly,
        50, 50, 5, camp, 100, 10, 0.15f, 0.10f, 30)
    {
        SetStory("高攻击力，低血量。");
        AddSkill(std::make_shared<NormalAttackSkill>());
    }

};

