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
    auto &fm = FightManager::GetInstance();
    char input;

    do
    {
        LogManager::PrintByChar("输入j进行普通攻击，输入k释放技能：\n");
        std::cin >> input;
        std::cin.ignore(256, '\n'); // 清除输入缓冲区

        if (input == 'j')
        {
            fm.GetPlayerFightPoke()->Attack(fm.GetEnemyFightPoke()->ModelPtr);
            break;
        }
        else if (input == 'k')
        {
            // TODO: 释放技能
            break;
        }
        else
        {
            LogManager::PrintByChar("非法输入，请重新输入（只能输入j或k）\n",
                                    LogColor::Red);
        }
    } while (true);
}

void PlayerFightState::OnExit()
{
    LogManager::PrintByChar("============");
    LogManager::PrintByChar("你的回合结束了",
                            LogColor::Yellow);
    LogManager::PrintByChar("============\n");
}
