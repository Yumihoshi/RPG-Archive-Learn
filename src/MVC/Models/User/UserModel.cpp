/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午1:41
* @version: 1.0
* @description: 
*******************************************************************************/
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "../../../../include/Managers/PokeManager.h"
#include "../../../../include/MVC/Models/User/UserModel.h"

const std::string UserModel::USER_FILE = "../data/users.txt";

UserModel::UserModel() : _userType(UserType::NormalPlayer)
{
    // 获取当前时间并转换为无符号整数作为 _id
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    _id = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

UserModel::UserModel(std::string username, std::string password, UserType type)
        : _username(std::move(username)),
          _password(std::move(password)),
          _userType(type)
{
    // 获取当前时间并转换为无符号整数作为 _id
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    _id = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

UserModel::UserModel(std::string username, std::string password, UserType type,
                     unsigned int id)
        : _username(std::move(username)),
          _password(std::move(password)),
          _userType(type),
          _id(id)
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

std::string UserModel::Decrypt(const std::string &encryptedPassword)
{
    std::string decrypted = encryptedPassword;
    for (char &c: decrypted)
    {
        c = (c - 7 + 128) % 128; // 简单的移位解密
    }
    return decrypted;
}

// Getter实现
unsigned int UserModel::GetId() const
{ return _id; }

std::string UserModel::GetUsername() const
{ return _username; }

UserType UserModel::GetUserType() const
{ return _userType; }

std::string UserModel::GetEncryptPassword() const
{ return _password; }

std::string UserModel::GetOriginPassword() const
{ return Decrypt(_password); }

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
            unsigned int id; // 不再使用该变量
            int userTypeInt;
            if (iss >> id >> username >> password >> userTypeInt)
            {
                auto userType = static_cast<UserType>(userTypeInt);
                UserModel user(username, password, userType, id);
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
                 << " " << static_cast<int>(user._userType) << " " << user._isFirstTime << "\n";
        }
        file.close();
    }
}

std::shared_ptr<UserModel> UserModel::FindUserById(unsigned int id)
{
    auto users = LoadUsersFromFile(USER_FILE);
    auto it = std::find_if(users.begin(), users.end(),
                           [id](const UserModel &user) {
                               return user.GetId() == id;
                           });
    if (it!= users.end())
        return std::make_shared<UserModel>(*it);
    else
        return nullptr;
}
