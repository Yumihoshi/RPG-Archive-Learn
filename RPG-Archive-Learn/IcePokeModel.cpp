#include <iostream>
#include "IcePokeModel.h"
#include "LogManager.h"
#include "Common.h"

void IcePokeModel::TakeDamage(int amount)
{
    BasePokeModel::TakeDamage(amount - _defendValue);
}

void IcePokeModel::PerturbAttribute()
{
    BasePokeModel::PerturbAttribute();
    _defendValue *= Common::GetInstance().GetRandomFloat(0.9f, 1.1f);
}

int IcePokeModel::GetDefendValue()
{
    return _defendValue;
}
