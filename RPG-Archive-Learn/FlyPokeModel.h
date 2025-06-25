#pragma once
#include "BasePokeModel.h"
class FlyPokeModel :public BasePokeModel
{
	FlyPokeModel(string name, int maxHp, int maxMp, int turnRecoverMp,
		CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate) :BasePokeModel(name, ElementType::Fly,
			maxHp, maxMp, turnRecoverMp, camp, maxExp, maxLevel, critRate, fleeRate)
	{

	}

};

