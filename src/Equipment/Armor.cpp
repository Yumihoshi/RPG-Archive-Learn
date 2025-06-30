#include "../../include/Equipment/Armor.h"
#include "../../include/MVC/Models/Poke/BasePokeModel.h"

void Armor::ShowInfo()
{
    std::cout << "显示防具" << std::endl;
}

void Armor::ApplyEffect()
{
    Owner->SetMaxHp(Owner->GetMaxHp() + MaxHpBonus);
    Owner->SetFleeRate(Owner->GetFleeRate() + FleeRateBonus);
}

void Armor::RemoveEffect()
{
    Owner->SetMaxHp(Owner->GetMaxHp() - MaxHpBonus);
    Owner->SetFleeRate(Owner->GetFleeRate() - FleeRateBonus);
}
