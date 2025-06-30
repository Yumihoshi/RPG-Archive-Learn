#include <iostream>
#include "../../../../include/MVC/Views/User/UserView.h"

// 显示登录菜单
void UserView::ShowLoginMenu()
{
    std::cout << "1. 注册\n2. 登录\n3. 退出\n请选择: ";
}

// 显示注册成功信息
void UserView::ShowRegistrationSuccess()
{
    std::cout << "注册成功！\n";
}

// 显示登录成功信息
void UserView::ShowLoginSuccess(const std::string &username)
{
    std::cout << "欢迎，" << username << "！登录成功！\n";
}

// 显示输入错误信息
void UserView::ShowInputError(const std::string &message)
{
    std::cout << message << "\n";
}

// 获取用户名输入
std::string UserView::GetUsernameInput()
{
    std::string username;
    std::cout << "请输入用户名: ";
    std::cin >> username;
    return username;
}

// 获取密码输入
std::string UserView::GetPasswordInput()
{
    std::string password;
    std::cout << "请输入密码: ";
    std::cin >> password;
    return password;
}
