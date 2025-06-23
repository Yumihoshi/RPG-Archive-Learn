#pragma once
#include "PokemonModel.h"
class IcePokeModel : public PokemonModel
{
public:
    IcePokeModel(string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) : PokemonModel(name, ele,
            maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
    {
    }

    void TakeDamage(int amount) override;
private:
    int _defendValue = 15;        // 魔法盾防御值
};

