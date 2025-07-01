/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午8:29
* @version: 1.0
* @description: 
*******************************************************************************/
#include <memory>
#include <algorithm>
#include <cstdlib>
#include "../../include/Managers/UserManager.h"
#include "../../include/MVC/Controllers/User/UserController.h"
#include "../../include/Managers/LogManager.h"


// 注册用户
void UserManager::RegisterUser()
{
    auto model = std::make_shared<UserModel>();
    auto view = std::make_shared<UserView>();
    UserController controller(model, view);
    auto users = UserModel::LoadUsersFromFile(model->USER_FILE);
    controller.RegisterUser(users);
}

// 用户登录
bool UserManager::LoginUser()
{
    auto model = std::make_shared<UserModel>();
    auto view = std::make_shared<UserView>();
    UserController controller(model, view);
    auto users = UserModel::LoadUsersFromFile(model->USER_FILE);
    bool isLoggedIn = controller.LoginUser(users);

    if (isLoggedIn)
    {
        // 直接从控制器的模型获取已登录用户
        for (const auto &user: users)
        {
            if (user.GetUsername() == controller.GetModel()->GetUsername())
            {
                _curUser = std::make_shared<UserModel>(user);
                break;
            }
        }
    }
    return isLoggedIn;
}

#include "../../include/Managers/PokeManager.h"
#include "../../include/MVC/Models/Poke/FirePokeModel.h"
#include "../../include/MVC/Models/Poke/GrassPokeModel.h"
#include "../../include/MVC/Models/Poke/IcePokeModel.h"

// 用户登录循环
void UserManager::StartLoop()
{
    while (true)
    {
        LogManager::PrintByChar("\n========");
        LogManager::PrintByChar("用户系统", LogColor::Yellow);
        LogManager::PrintByChar("========\n");
        auto view = std::make_shared<UserView>();
        view->ShowLoginMenu();
        std::string choice;
        std::cin >> choice;

        if (choice == "1")
            RegisterUser();
        else if (choice == "2")
        {
            if (LoginUser())
            {
                if (GetCurrentUser()->IsFirstTime())
                {
                    DialogueManager::GetInstance().ShowStory({"game_intro_1", "game_intro_2", "game_intro_3"});
                    LogManager::PrintByChar("欢迎新玩家！请选择你的初始宝可梦：\n");
                    LogManager::PrintByChar("1. 火属性\n");
                    LogManager::PrintByChar("2. 草属性\n");
                    LogManager::PrintByChar("3. 冰属性\n");
                    std::string pokeChoice;
                    std::cin >> pokeChoice;
                    if (pokeChoice == "1")
                    {
                        auto poke = std::make_shared<FirePokeModel>(PokeManager::GetInstance().GetPokeDefaultNameByElement(ElementType::Fire), CampType::Friend);
                        PokeManager::GetInstance().AddPoke(ElementType::Fire, poke);
                    }
                    else if (pokeChoice == "2")
                    {
                        auto poke = std::make_shared<GrassPokeModel>(PokeManager::GetInstance().GetPokeDefaultNameByElement(ElementType::Grass), CampType::Friend);
                        PokeManager::GetInstance().AddPoke(ElementType::Grass, poke);
                    }
                    else if (pokeChoice == "3")
                    {
                        auto poke = std::make_shared<IcePokeModel>(PokeManager::GetInstance().GetPokeDefaultNameByElement(ElementType::Ice), CampType::Friend);
                        PokeManager::GetInstance().AddPoke(ElementType::Ice, poke);
                    }
                    GetCurrentUser()->SetFirstTime(false);
                UIManager::GetInstance().ShowArchiveMenu();
                break;
            }
        }
        else if (choice == "3")
        {
            LogManager::PrintByChar("系统已退出！\n");
            std::exit(0);
        }
        else
            LogManager::PrintByChar("无效选择，请重新输入！\n", LogColor::Red);
    }
}

