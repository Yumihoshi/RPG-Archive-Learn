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
                // TODO: 登录后的操作
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

