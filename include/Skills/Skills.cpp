//
// Created by ASUS on 25-6-30.
//
#include "Skills.h"
#include "../Managers/LogManager.h"
#include "../Common/Types.h"
#include "../Managers/FightManager.h"

void SkillHandler::useSkill(Skills skill) {
    const auto trigger = FightManager::GetInstance().GetPlayerFightPoke();
    const auto target = FightManager::GetInstance().GetEnemyFightPoke();
    switch (skill) {
        case Skills::Fire:
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了烈火连爆！\n");
            
            break;
        case Skills::Ice:
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了寒霜凝滞！\n");
            break;
        case Skills::Grass:
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了青藤焕生！\n");
            trigger->ModelPtr->Heal(20);
            break;
        case Skills::Fly:
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了空影迷踪！\n");
            break;
        case Skills::Ghost:
            LogManager::PrintByChar(trigger->ModelPtr->GetName() + " 使用了鬼雾蚀力！\n");
            break;
        default:
            break;
    }
}
