#pragma once

#include "BasePokeModel.h"

class IcePokeModel : public BasePokeModel
{
public:
    IcePokeModel(std::string name, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) : BasePokeModel(name, ElementType::Ice,
            maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
    {
    }

    void TakeDamage(int amount) override;
private:
    int _defendValue = 15;        // 魔法盾防御值
    bool CheckFlee();
};

