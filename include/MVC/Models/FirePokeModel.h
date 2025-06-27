#pragma once

#include "BasePokeModel.h"
#include "../../Common/Types.h"

class FirePokeModel : public BasePokeModel
{
public:
    FirePokeModel(std::string name, CampType camp) : BasePokeModel(name, ElementType::Fire,
        120, 30, 5, camp, 100, 10l, 0.2f, 0.1f, 8)
    {
        PerturbAttribute();
        ResetCur();
        SetStory("高生命值，低魔法值，在某次洪灾中牺牲自己，救下了人们，后被念时复活。");
    }
private:
};

