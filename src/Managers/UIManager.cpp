#include <iostream>
#include <string>
#include "../../include/Managers/UIManager.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Common/Common.h"
#include "../../include/MVC/Models/User/UserModel.h"
#include "../../include/Managers/UserManager.h"

UIManager::UIManager() = default;

// 显示主菜单
void UIManager::ShowPokeManagerMainMenu()
{
    LogManager::PrintByChar("\n==============================\n");
    LogManager::PrintByChar("        空可梦管理系统       \n",
                            LogColor::Yellow);
    LogManager::PrintByChar("==============================\n"
                            "输入 p 查看所有空可梦\n"
                            "输入 A 进入战斗\n"
                            "输入 s 存档\n"
                            "输入 exit 退出游戏\n"
                            "==============================\n");
}

// 显示所有空可梦
void UIManager::ShowAllPokesInfo()
{
    auto &pokeMap = PokeManager::GetInstance().GetAllPokes();
    LogManager::PrintByChar("\n当前所有空可梦：\n"
                            "ID\t名称\t\t防具\t\t饰品\n"
                            "----------------------------------------------");
    for (const auto &p: pokeMap)
    {
        for (const auto &poke: p.second)
        {
            LogManager::PrintByChar(std::to_string(poke->GetId()));
            LogManager::PrintByChar("\t" + poke->GetName());

            if (poke->GetArmor() == nullptr)
                LogManager::PrintByChar("无\n");
            else
                LogManager::PrintByChar(poke->GetArmor()->Name + "\n");
            if (poke->GetDecoration() == nullptr)
                LogManager::PrintByChar("无\n");
            else
                LogManager::PrintByChar(poke->GetDecoration()->Name + "\n");
        }
    }
}

void
UIManager::ShowEquipManagerMenu(const std::shared_ptr<BasePokeModel> &model)
{
    // TODO: 完善下面的逻辑
    while (true)
    {
        LogManager::PrintByChar("\n当前空可梦: " + model->GetName() + "\n");
        LogManager::PrintByChar("1. 防具: ");
        if (model->GetArmor() == nullptr)
            LogManager::PrintByChar("无\n");
        else
            LogManager::PrintByChar(model->GetArmor()->Name + "\n");

        LogManager::PrintByChar("2. 饰品: ");
        if (model->GetDecoration() == nullptr)
            LogManager::PrintByChar("无\n");
        else
            LogManager::PrintByChar(model->GetDecoration()->Name + "\n");

        LogManager::PrintByChar("-----------------------------\n"
                                "输入 a1 替换/装备防具\n"
                                "输入 a2 卸下防具\n"
                                "输入 d1 替换/装备饰品\n"
                                "输入 d2 卸下饰品\n"
                                "输入 exit 返回主菜单\n");

        std::string input;
        LogManager::PrintByChar("\n请输入指令:");
        getline(std::cin, input);
        input = Common::ToLower(input);

        if (input == "exit")
            break;
        else if (input == "a1")
        {
            LogManager::PrintByChar("请输入新的防具id: ");
            // TODO: 替换/装备防具逻辑
            //            getline(std::cin, model->armor);
            LogManager::PrintByChar("防具已装备！\n");
        }
        else if (input == "a2")
        {
            model->Unequip(EquipType::Armor);
            LogManager::PrintByChar("防具已卸下！\n");
        }
        else if (input == "d1")
        {
            LogManager::PrintByChar("请输入新的饰品id: ");
            // TODO: 替换/装备饰品逻辑
            // getline(cin, model->decoration);
            LogManager::PrintByChar("饰品已装备！\n");
        }
        else if (input == "d2")
        {
            model->Unequip(EquipType::Decoration);
            LogManager::PrintByChar("饰品已卸下！\n");
        }
        else
        {
            // TODO: 完善指令
        }
    }
}

void UIManager::HandleUserInput()
{
    auto &userManager = UserManager::GetInstance();
    std::shared_ptr<UserModel> user = userManager.GetCurrentUser();

    while (true)
    {
        ShowPokeManagerMainMenu();
        std::string input;
        LogManager::PrintByChar("\n请输入指令:");
        getline(std::cin, input);
        input = Common::ToLower(input);

        if (input == "exit")
        {
            break;
        }
        else if (input == "p")
        {
            ShowAllPokesInfo();
        }
        else if (input == "a")
        {
            // 进入战斗逻辑
        }
        else if (input == "s")
        {
            int slot;
            LogManager::PrintByChar("请输入存档槽位 (0 - 2): ");
            std::cin >> slot;
            std::cin.ignore();
            if (slot >= 0 && slot < 3)
            {
                user->SaveArchive(slot);
                LogManager::PrintByChar("存档保存成功！\n");
            }
            else
            {
                LogManager::PrintByChar("无效的存档槽位！\n");
            }
        }
        else if (input == "l")
        {
            int slot;
            LogManager::PrintByChar("请输入存档槽位 (0 - 2): ");
            std::cin >> slot;
            std::cin.ignore();
            if (slot >= 0 && slot < 3)
            {
                user->LoadArchive(slot);
                LogManager::PrintByChar("存档加载成功！\n");
            }
            else
            {
                LogManager::PrintByChar("无效的存档槽位！\n");
            }
        }
        else if (input == "d")
        {
            int slot;
            LogManager::PrintByChar("请输入存档槽位 (0 - 2): ");
            std::cin >> slot;
            std::cin.ignore();
            if (slot >= 0 && slot < 3)
            {
                user->DeleteArchive(slot);
                LogManager::PrintByChar("存档删除成功！\n");
            }
            else
            {
                LogManager::PrintByChar("无效的存档槽位！\n");
            }
        }
        else if (input == "i")
        {
            user->ShowArchiveInfo();
        }
        else
        {
            LogManager::PrintByChar("无效指令，请重新输入！\n");
        }
    }
    LogManager::PrintByChar("无效指令，请重新输入！\n");
}
