#pragma once
#include "PokemonModel.h"
class NaturePokeModel : public PokemonModel
{
public:
    NaturePokeModel(string name, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) : PokemonModel(name, ElementType::Nature,
            maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
    {
    }
private:
};

