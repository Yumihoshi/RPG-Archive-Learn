//
// Created by ASUS on 25-6-30.
//
#include "Skills.h"
#pragma once
#include "../Managers/LogManager.h"
#include "../Common/Types.h"
#include "../Managers/FightManager.h"

void SkillHandler::useSkill(Skills skill) {
    auto trigger = FightManager::GetInstance()
    switch (skill) {
        case Skills::Fire:
            LogManager::PrintByChar(->GetName() + " 使用了烈火连爆！\n");

            break;
        case Skills::Ice:
            LogManager::PrintByChar(trigger->GetName() + " 使用了寒霜凝滞！\n");
            break;
        case Skills::Grass:
            LogManager::PrintByChar(trigger->GetName() + " 使用了青藤焕生！\n");
            trigger->Heal(20);
            break;
        case Skills::Fly:
            LogManager::PrintByChar(trigger->GetName() + " 使用了空影迷踪！\n");
            break;
        case Skills::Ghost:
            LogManager::PrintByChar(trigger->GetName() + " 使用了鬼雾蚀力！\n");
            break;
        default:
            break;
    }
}
