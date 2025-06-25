#pragma once
#include "BaseEquipment.h"
class Weapon:public BaseEquipment
{
public:
	int AttackBonus;
	int MaxMpBonus;
	float CritRateBonus;
};

