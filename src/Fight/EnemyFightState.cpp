/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午4:36
* @version: 1.0
* @description: 
*******************************************************************************/
#include "../../include/Fight/EnemyFightState.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Managers/FightManager.h"
#include "../../include/Skills/NormalAttackSkill.h"

void EnemyFightState::OnEnter()
{
    LogManager::PrintByChar("===========");
    LogManager::PrintByChar("现在轮到敌人的回合了",
                            LogColor::Red);
    LogManager::PrintByChar("===========\n");
}

void EnemyFightState::Handle()
{
    auto &fm = FightManager::GetInstance();

    // 敌人自动进行普通攻击
    NormalAttackSkill normalAttack;
    normalAttack.Use(fm.GetEnemyFightPoke()->ModelPtr, fm.GetPlayerFightPoke()->ModelPtr);
}

void EnemyFightState::OnExit()
{
    // 攻击后切换回玩家回合
    LogManager::PrintByChar("===========");
    LogManager::PrintByChar("敌人的回合结束了",
                            LogColor::Red);
    LogManager::PrintByChar("===========\n");
}");
    LogManager::PrintByChar("现在轮到敌人的回合了",
                            LogColor::Red);
    LogManager::PrintByChar("============\n");
}

void EnemyFightState::Handle()
{
    auto &fm = FightManager::GetInstance();

    // 敌人自动进行普通攻击
    fm.GetEnemyFightPoke()->Attack(fm.GetPlayerFightPoke()->ModelPtr);
}

void EnemyFightState::OnExit()
{
    // 攻击后切换回玩家回合
    LogManager::PrintByChar("============");
    LogManager::PrintByChar("敌人的回合结束了",
                            LogColor::Red);
    LogManager::PrintByChar("============\n");
}
