#pragma once

#include "BasePokeModel.h"
#include "Types.h"

class FirePokeModel : public BasePokeModel
{
public:
    FirePokeModel(string name, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) : BasePokeModel(name, ElementType::Fire,
            maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
    {
    }

    void TakeDamage(int amount) override;
private:
};

