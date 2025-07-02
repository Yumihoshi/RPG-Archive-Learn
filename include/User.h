#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <map>
#include "Pokemon.h"

class User {
public:
    enum UserType { PLAYER, ADMIN };

    User(std::string username, std::string password, UserType type);

    std::string getUsername() const;
    std::string getPassword() const;
    UserType getUserType() const;
    void setPassword(const std::string& newPassword);

    // Player specific data
    std::vector<std::vector<Pokemon>> saveSlots; // Three save slots, each containing a vector of Pokemon

private:
    std::string username;
    std::string password;
    UserType type;
};

class UserManager {
public:
    UserManager();
    User* login(const std::string& username, const std::string& password);
    void registerUser(const std::string& username, const std::string& password, User::UserType type);
    void saveUsers();
    void loadUsers();

    // Admin functionalities
    void createUser(const std::string& username, const std::string& password, User::UserType type);
    void deleteUser(const std::string& username);
    void updateUserPassword(const std::string& username, const std::string& newPassword);
    void listAllUsers() const;
    User* getUserByUsername(const std::string& username) const;

private:
    std::map<std::string, User*> users; // Map username to User object

    // Helper to get file path for user data
    std::string getUserDataFilePath() const;
};

#endif // USER_H
