#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <map>
#include "../Poke/Pokemon.h"

class User
{
public:
    enum UserType
    {
        PLAYER, ADMIN
    };

    User(std::string username, std::string password, UserType type);

    std::string getUsername() const;

    std::string getPassword() const;

    UserType getUserType() const;

    void setPassword(const std::string &newPassword);

    // Player specific data
    std::vector<std::vector<std::shared_ptr<Pokemon>>> saveSlots; // 存档槽

private:
    std::string username;
    std::string password;
    UserType type;
};

#endif // USER_H
