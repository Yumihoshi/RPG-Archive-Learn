#include <iostream>
#include <string>
#include "../../include/Managers/UIManager.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Common/Common.h"
#include "../../include/MVC/Models/User/UserModel.h"
#include "../../include/Managers/UserManager.h"
#include "../../include/Managers/GameManager.h"

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

// 根据当前用户权限类型，显示不同的菜单
void UIManager::ShowCurUserSpecificMenu()
{
    switch (UserManager::GetInstance().GetCurrentUser()->GetUserType())
    {
        case UserType::NormalPlayer:
            ShowPlayerMenu();
            break;
        case UserType::Admin:
            ShowAdminMenu();
            // TODO: 显示用户宝可梦及操作
            break;
    }
}

// 新增玩家菜单
void UIManager::ShowPlayerMenu()
{
    //TODO: 完善下面的逻辑
    while (true)
    {
        LogManager::PrintByChar("输入p查看所有宝可梦，输入f进入战斗”,输入s存档，输入exit退出游戏\n");
        std::cin.ignore();
        std::string input;
        getline(std::cin, input);
        if (input == "p")
        {

        }
        else if (input == "f")
        {

        }
        else if (input == "s")
        {

        }
        else if (input == "exit")
        {
            std::exit(0);
        }
        else
        {
            LogManager::PrintByChar("无效输入！\n");
            continue;
        }
    }
}

// 新增管理员菜单
void UIManager::ShowAdminMenu()
{
    while (true)
    {
        ShowAllUsersInfo();
        std::string input;
        LogManager::PrintByChar("\n请输入用户ID或指令:\n");
        std::cin.ignore();
        getline(std::cin, input);
        std::shared_ptr<UserModel> user = nullptr;

        try
        {
            unsigned int id = std::stoul(input);
            user = UserModel::FindUserById(id);
        }
        catch (...)
        {
            LogManager::PrintByChar("无效输入！请输入数字ID或exit\n",
                                    LogColor::Red);
            break;
        }

        if (user != nullptr)
        {
            LogManager::PrintByChar("选中用户: " + user->GetUsername() + "\n");
            GameManager::GetInstance().AdminSelectedUser = user;
            return;
        }
        else
        {
            LogManager::PrintByChar("未找到用户！\n", LogColor::Red);
        }
    }
}

// 显示所有用户信息
void UIManager::ShowAllUsersInfo()
{
    auto users = UserModel::LoadUsersFromFile(UserModel::USER_FILE);
    LogManager::PrintByChar("======所有用户信息======\n");
    for (const auto &user: users)
    {
        LogManager::PrintByChar("ID: " + std::to_string(user.GetId()) + "\n");
        LogManager::PrintByChar("用户名: " + user.GetUsername() + "\n");
        LogManager::PrintByChar(
                "密码: " + user.GetOriginPassword() + "\n");
        LogManager::PrintByChar("用户类型: ");
        LogManager::PrintByChar(user.GetUserType() == UserType::NormalPlayer
                                ? "普通玩家" : "管理员");
        LogManager::PrintByChar("\n\n");
    }
    LogManager::PrintByChar("请输入要操作的用户ID：\n");
}
