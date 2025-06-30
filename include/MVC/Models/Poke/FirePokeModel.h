#pragma once

#include <utility>

#include "BasePokeModel.h"
#include "../../../Common/Types.h"

class FirePokeModel : public BasePokeModel
{
public:
    // 剩余必定暴击次数
    int CritCount = 0;
public:
    FirePokeModel(std::string name, CampType camp) : BasePokeModel(std::move(name), ElementType::Fire,
        120, 30, 5, camp, 100, 10l, 0.2f, 0.1f, 8)
    {
        SetStory("高生命值，低魔法值，在某次洪灾中牺牲自己，救下了人们，后被念时复活。");
    }
private:
};

