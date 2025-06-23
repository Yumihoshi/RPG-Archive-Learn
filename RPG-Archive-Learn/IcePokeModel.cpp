#include "IcePokeModel.h"

void IcePokeModel::TakeDamage(int amount)
{
    // 冰属性自带防御
    PokemonModel::TakeDamage(amount - _defendValue);
}
