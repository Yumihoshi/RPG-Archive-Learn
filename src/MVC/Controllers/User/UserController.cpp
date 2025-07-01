/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午7:14
* @version: 1.0
* @description: 
*******************************************************************************/
#include <utility>
#include <fstream>
#include <algorithm>
#include "../../../../include/MVC/Controllers/User/UserController.h"
#include "../../../../include/Managers/LogManager.h"


UserController::UserController(std::shared_ptr<UserModel> model,
                               std::shared_ptr<UserView> view)
{
    _model = std::move(model);
    _view = std::move(view);
}

// 处理注册
bool UserController::RegisterUser(std::vector<UserModel> &users)
{
    std::string username = _view->GetUsernameInput();
    auto it = std::find_if(users.begin(), users.end(),
                           [&username](const UserModel &user) {
                               return user.GetUsername() == username;
                           });
    if (it != users.end())
    {
        _view->ShowInputError("用户名已存在，请重新选择！");
        return false;
    }
    std::string password = _view->GetPasswordInput();
    password = UserModel::Encrypt(password);
    UserModel newUser(username, password);
    users.push_back(newUser);
    UserModel::SaveUsersToFile(users, UserModel::USER_FILE);
    _view->ShowRegistrationSuccess();
    return true;
}

// 处理登录
bool UserController::LoginUser(const std::vector<UserModel> &users)
{
    std::string username = _view->GetUsernameInput();
    std::string password = _view->GetPasswordInput();
    auto it = std::find_if(users.begin(), users.end(),
                           [&username, &password](const UserModel &user) {
                               return user.GetUsername() == username &&
                                       user.GetEncryptPassword() ==
                                       UserModel::Encrypt(password);
                           });
    if (it != users.end())
    {
        _model = std::make_shared<UserModel>(*it);
        _view->ShowLoginSuccess(username);
        return true;
    }
    _view->ShowInputError("用户名或密码错误，请重新输入！");
    return false;
}

// 获取密码输入
std::string UserController::GetPassword(const char *prompt)
{
    std::string password;
    LogManager::PrintByChar(prompt);
    getline(std::cin, password);

    return password;
}
