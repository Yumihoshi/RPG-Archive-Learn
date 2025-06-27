#include <iostream>
#include "../../../include/MVC/Models/IcePokeModel.h"
#include "../../../include/Managers/LogManager.h"
#include "../../../include/Common/Common.h"

void IcePokeModel::TakeDamage(int amount)
{
    BasePokeModel::TakeDamage(amount - _defendValue);
}

void IcePokeModel::PerturbAttribute()
{
    BasePokeModel::PerturbAttribute();
    _defendValue *= Common::GetRandomFloat(0.9f, 1.1f);
}

int IcePokeModel::GetDefendValue() const
{
    return _defendValue;
}
