#pragma once
#include "BasePokeModel.h"
class GhostPokeModel :public BasePokeModel
{
	GhostPokeModel(string name, int maxHp, int maxMp, int turnRecoverMp,
		CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) :BasePokeModel(name, ElementType::Ghost,
			maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
	{

	}

};
