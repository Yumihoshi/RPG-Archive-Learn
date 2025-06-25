#pragma once

#include "BasePokeModel.h"

class NaturePokeModel : public BasePokeModel
{
public:
    NaturePokeModel(string name, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) : BasePokeModel(name, ElementType::Nature,
            maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
    {
    }
private:
};

