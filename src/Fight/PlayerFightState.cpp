/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午2:54
* @version: 1.0
* @description: 
*******************************************************************************/
#include "../../include/Fight/PlayerFightState.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Managers/FightManager.h"

void PlayerFightState::OnEnter()
{
    LogManager::PrintByChar("============");
    LogManager::PrintByChar("现在轮到你的回合了",
                                          LogColor::Yellow);
    LogManager::PrintByChar("============\n");
}

void PlayerFightState::Handle()
{
    LogManager::PrintByChar("输入j进行普通攻击，输入k释放技能：\n");
}

void PlayerFightState::OnExit()
{

}
