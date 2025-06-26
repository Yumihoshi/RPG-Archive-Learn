#pragma once
#include "BasePokeModel.h"
class FlyPokeModel :public BasePokeModel
{
public:
    FlyPokeModel(std::string name, CampType camp) :BasePokeModel(name, ElementType::Fly,
        50, 50, 5, camp, 100, 10, 0.15, 0.10, 30)
    {
        PerturbAttribute();
        ResetCur();
        SetStory("高攻击力，低血量。");
    }

};

