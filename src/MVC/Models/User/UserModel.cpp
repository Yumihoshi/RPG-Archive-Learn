/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午1:41
* @version: 1.0
* @description: 
*******************************************************************************/
#include "../../../../include/MVC/Models/User/UserModel.h"
#include <fstream>
#include <sstream>

// 初始化静态成员
unsigned int UserModel::s_nextId = 1;

UserModel::UserModel() : _id(s_nextId++), _userType(UserType::NormalPlayer)
{
}

UserModel::UserModel(std::string username, std::string password, UserType type)
        : _id(s_nextId++),
          _username(std::move(username)),
          _password(std::move(password)),
          _userType(type)
{
}

std::string UserModel::Encrypt(const std::string &password)
{
    std::string encrypted = password;
    for (char &c: encrypted)
    {
        c = (c + 7) % 128; // 简单的移位加密
    }
    return encrypted;
}

// Getter实现
unsigned int UserModel::GetId() const
{ return _id; }

std::string UserModel::GetUsername() const
{ return _username; }

UserType UserModel::GetUserType() const
{ return _userType; }

std::string UserModel::GetPassword() const
{ return _password; }

std::string UserModel::GetEncryptedPassword() const
{ return Encrypt(_password); }

// Setter实现
void UserModel::SetUsername(const std::string &username)
{ _username = username; }

void UserModel::SetPassword(const std::string &password)
{ _password = password; }

void UserModel::SetUserType(UserType type)
{ _userType = type; }


// 从文件加载用户数据
std::vector<UserModel> UserModel::LoadUsersFromFile(const std::string &filePath)
{
    std::vector<UserModel> users;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string username, password;
            unsigned int id;
            int userTypeInt;
            if (iss >> id >> username >> password >> userTypeInt)
            {
                auto userType = static_cast<UserType>(userTypeInt);
                UserModel user(username, password, userType);
                user._id = id;
                users.push_back(user);
            }
        }
        file.close();
    }
    return users;
}

// 将用户数据保存到文件
void UserModel::SaveUsersToFile(const std::vector<UserModel> &users,
                                const std::string &filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        for (const auto &user: users)
        {
            file << user._id << " " << user._username << " " << user._password
                 << " " << static_cast<int>(user._userType) << "\n";
        }
        file.close();
    }
}
