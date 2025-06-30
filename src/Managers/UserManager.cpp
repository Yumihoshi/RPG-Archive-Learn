/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午8:29
* @version: 1.0
* @description: 
*******************************************************************************/
#include <memory>
#include <algorithm>
#include "../../include/Managers/UserManager.h"
#include "../../include/MVC/Controllers/User/UserController.h"


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

// 获取当前登录用户
const UserModel& UserManager::GetCurUser() const
{
    return *_curUser; // 保持原有接口兼容
}

