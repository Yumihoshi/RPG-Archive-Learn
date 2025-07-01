#include <iostream>
#include "../../../../include/MVC/Views/User/UserView.h"
#include "../../../../include/Managers/LogManager.h"

// 显示登录菜单
void UserView::ShowLoginMenu()
{
    LogManager::PrintByChar("1. 注册\n"
                            "2. 登录\n"
                            "3. 退出\n"
                            "请选择: ");
}

// 显示注册成功信息
void UserView::ShowRegistrationSuccess()
{
    LogManager::PrintByChar("注册成功！\n", LogColor::Green);
}

// 显示登录成功信息
void UserView::ShowLoginSuccess(const std::string &username)
{
    LogManager::PrintByChar("欢迎，" + username + "！登录成功！\n", LogColor::Green);
}

// 显示输入错误信息
void UserView::ShowInputError(const std::string &message)
{
    LogManager::PrintByChar(message + "\n", LogColor::Red);
}

// 获取用户名输入
std::string UserView::GetUsernameInput()
{
    std::string username;
    LogManager::PrintByChar("请输入用户名: ");
    std::cin >> username;
    return username;
}

// 获取密码输入
std::string UserView::GetPasswordInput()
{
    std::string password;
    LogManager::PrintByChar("请输入密码：");
    std::cin >> password;
    return password;
}
