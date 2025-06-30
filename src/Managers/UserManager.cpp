/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午8:29
* @version: 1.0
* @description: 
*******************************************************************************/
#include <memory>
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
    return controller.LoginUser(users);
}
