/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/27 下午2:20
* @version: 1.0
* @description: 
*******************************************************************************/
#include <fstream>
#include <conio.h>
#include "../../include/Managers/UserManager.h"
#include "../../include/Managers/LogManager.h"

UserManager::UserManager() = default;

std::string UserManager::Encrypt(const std::string &password)
{
    std::string encrypted = password;
    for (char &c: encrypted)
    {
        c = (c + 7) % 128; // 简单的移位加密
    }
    return encrypted;
}

bool UserManager::IsUsernameAlreadyExist(const std::string &username)
{
    // 检查用户名是否已存在

    std::ifstream file(USER_FILE);
    std::string line, savedUser;

    while (getline(file, line))
    {
        size_t pos = line.find(' ');
        if (pos != std::string::npos)
        {
            savedUser = line.substr(0, pos);
            if (savedUser == username)
            {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;

}

// 用户注册
void UserManager::RegisterUser()
{
    LogManager::PrintByChar("\n===== 用户注册 =====\n");
    std::string username, password1, password2;

    LogManager::PrintByChar("请输入用户名: \n");
    getline(std::cin, username);

    // 检查用户名是否为空
    if (username.empty())
    {
        LogManager::PrintByChar("用户名不能为空！\n", LogColor::Red);
        return;
    }

    // 检查用户名是否已存在
    if (IsUsernameAlreadyExist(username))
    {
        LogManager::PrintByChar("用户名已存在，请选择其他用户名！\n",
                                LogColor::Red);
        return;
    }

    // 获取并验证密码
    password1 = GetPassword("请输入密码: \n");
    password2 = GetPassword("请确认密码: \n");

    if (password1 != password2)
    {
        LogManager::PrintByChar("两次输入的密码不一致！\n", LogColor::Red);
        return;
    }

    if (password1.empty())
    {
        LogManager::PrintByChar("密码不能为空！\n", LogColor::Red);
        return;
    }

    // 保存用户信息
    std::ofstream outFile(USER_FILE, std::ios::app);
    outFile << username << " " << Encrypt(password1) << std::endl;
    outFile.close();

    LogManager::PrintByChar("注册成功！\n", LogColor::Green);
}

// 获取密码输入
std::string UserManager::GetPassword(const char *prompt)
{
    std::string password;
    LogManager::PrintByChar(prompt);
    getline(std::cin, password);

    return password;

}

// 用户登录
bool UserManager::LoginUser()
{
    LogManager::PrintByChar("\n===== 用户登录 =====\n");
    std::string username, password;

    LogManager::PrintByChar("用户名: \n");
    getline(std::cin, username);

    password = GetPassword("\n密码: \n");

    std::ifstream inFile(USER_FILE);
    std::string line, savedUser, savedPass;

    while (getline(inFile, line))
    {
        size_t pos = line.find(' ');
        if (pos != std::string::npos)
        {
            savedUser = line.substr(0, pos);
            savedPass = line.substr(pos + 1);

            if (savedUser == username && savedPass == Encrypt(password))
            {
                inFile.close();
                LogManager::PrintByChar("登录成功！欢迎回来，" + username + "！\n",
                                        LogColor::Green);
                return true;
            }
        }
    }

    inFile.close();
    LogManager::PrintByChar("用户名或密码错误！\n", LogColor::Red);
    return false;
}
