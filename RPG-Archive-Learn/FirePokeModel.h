#pragma once

#include "PokemonModel.h"

class FirePokeModel : public PokemonModel
{
public:
    FirePokeModel(string name, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) : PokemonModel(name, ElementType::Fire,
            maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
    {
    }

    void TakeDamage(int amount) override;
private:
    bool _isKuangBao = false;       // 是否处于狂暴状态
    int _KuangBaoZengShang = 20;         // 狂暴增伤数值
};

