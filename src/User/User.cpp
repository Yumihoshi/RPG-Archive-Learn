#include "../../include/User/User.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> // For JSON serialization/deserialization

// 用户
User::User(std::string username, std::string password, UserType type) :
        username(username),
        password(password),
        type(type)
{
    if (type == PLAYER)
    {
        saveSlots.resize(3); // 初始化3存档
    }
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

User::UserType User::getUserType() const
{
    return type;
}

void User::setPassword(const std::string &newPassword)
{
    password = newPassword;
}
