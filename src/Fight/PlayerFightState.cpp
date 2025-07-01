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
#include "../../include/Skills/NormalAttackSkill.h"

void PlayerFightState::OnEnter()
{
    LogManager::PrintByChar("===========");
    LogManager::PrintByChar("现在轮到你的回合了",
                            LogColor::Yellow);
    LogManager::PrintByChar("===========\n");
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
            NormalAttackSkill normalAttack;
            normalAttack.Use(fm.GetPlayerFightPoke()->ModelPtr, fm.GetEnemyFightPoke()->ModelPtr);
            break;
        }
        else if (input == 'k')
        {
            LogManager::PrintByChar("\n可用技能：\n");
            auto skills = fm.GetPlayerFightPoke()->ModelPtr->GetSkills();
            if (skills.empty())
            {
                LogManager::PrintByChar("你没有可用的技能！\n", LogColor::Red);
                continue;
            }
            for (size_t i = 0; i < skills.size(); ++i)
            {
                LogManager::PrintByChar(std::to_string(i + 1) + ". " + skills[i]->Name + " (消耗MP: " + std::to_string(skills[i]->MpCost) + ")\n");
            }
            LogManager::PrintByChar("请输入技能编号：");
            std::string skillChoiceStr;
            getline(std::cin, skillChoiceStr);
            try
            {
                int skillChoice = std::stoi(skillChoiceStr);
                if (skillChoice > 0 && skillChoice <= skills.size())
                {
                    auto skill = skills[skillChoice - 1];
                    if (fm.GetPlayerFightPoke()->ModelPtr->GetCurMp() >= skill->MpCost)
                    {
                        skill->Use(fm.GetPlayerFightPoke()->ModelPtr, fm.GetEnemyFightPoke()->ModelPtr);
                        fm.GetPlayerFightPoke()->ModelPtr->ReduceMp(skill->MpCost);
                        break;
                    }
                    else
                    {
                        LogManager::PrintByChar("魔法值不足！\n", LogColor::Red);
                    }
                }
                else
                {
                    LogManager::PrintByChar("无效的技能编号！\n", LogColor::Red);
                }
            }
            catch (const std::invalid_argument &e)
            {
                LogManager::PrintByChar("无效输入，请输入数字！\n", LogColor::Red);
            }
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
    LogManager::PrintByChar("===========");
    LogManager::PrintByChar("你的回合结束了",
                            LogColor::Yellow);
    LogManager::PrintByChar("===========\n");
}");
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
            float critRateBonus = 0.0f;
            if (fm.GetPlayerFightPoke()->ModelPtr->GetDecoration()) {
                critRateBonus = fm.GetPlayerFightPoke()->ModelPtr->GetDecoration()->CritRateBonus;
            }
            int damage = fm.GetPlayerFightPoke()->ModelPtr->CalculateDamage(critRateBonus);
            fm.GetEnemyFightPoke()->ModelPtr->TakeDamage(damage);
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
