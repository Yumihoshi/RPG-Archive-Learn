//
// Created by ASUS on 25-6-30.
//
#include "../../include/Skills/Skills.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Common/Types.h"
#include "../../include/Managers/FightManager.h"

void SkillHandler::useSkill(Skills skill)
{
    const auto trigger = FightManager::GetInstance().GetPlayerFightPoke();
    const auto target = FightManager::GetInstance().GetEnemyFightPoke();

    switch (skill) {
        case Skills::Fire:{
            auto m = std:: dynamic_pointer_cast<FirePokeModel>(trigger->ModelPtr);
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了烈火连爆！\n");
            m -> CritCount+=5;
            break;}
        case Skills::Ice: {
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了寒霜凝滞！\n");
            // 冰冻3回合
            break;
        }
        case Skills::Grass: {
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了青藤焕生！\n");
            trigger->ModelPtr->Heal(20);
            break;
        }
        case Skills::Fly: {
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了空影迷踪！\n");
            target->ModelPtr->SetFleeRate(target->ModelPtr->GetFleeRate() + 0.1);
            break;
        }
        case Skills::Ghost: {
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了鬼雾蚀力！\n");
            target->ModelPtr->SetDamage(target->ModelPtr->GetDamage()*0.9);
            break;
        }
        default:
            break;
    }
}
