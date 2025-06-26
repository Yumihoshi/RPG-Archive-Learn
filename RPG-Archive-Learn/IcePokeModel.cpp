#include <iostream>
#include "IcePokeModel.h"
#include "LogManager.h"

void IcePokeModel::TakeDamage(int amount)
{
    BasePokeModel::TakeDamage(amount - _defendValue);
}
