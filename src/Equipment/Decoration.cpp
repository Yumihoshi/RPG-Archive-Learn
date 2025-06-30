#include "../../include/Equipment/Decoration.h"
#include "../../include/MVC/Models/BasePokeModel.h"

void Decoration::ShowInfo()
{ 
    std::cout << "显示饰品" << std::endl;
}

void Decoration::ApplyEffect()
{
    Owner->SetDamage(Owner->GetDamage() + AttackBonus);
    Owner->SetMaxMp(Owner->GetMaxMp() + MaxMpBonus);
    Owner->SetCritRate(Owner->GetCritRate() + CritRateBonus);
    Owner->SetFleeRate(Owner->GetFleeRate() + FleeRateBonus);
}

void Decoration::RemoveEffect()
{
    Owner->SetDamage(Owner->GetDamage() - AttackBonus);
    Owner->SetMaxMp(Owner->GetMaxMp() - MaxMpBonus);
    Owner->SetCritRate(Owner->GetCritRate() - CritRateBonus);
    Owner->SetFleeRate(Owner->GetFleeRate() - FleeRateBonus);
}
