#include "User.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> // For JSON serialization/deserialization

// User class implementation
User::User(std::string username, std::string password, UserType type) :
    username(username),
    password(password),
    type(type) {
    if (type == PLAYER) {
        saveSlots.resize(3); // Initialize three empty save slots for players
    }
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

User::UserType User::getUserType() const {
    return type;
}

void User::setPassword(const std::string& newPassword) {
    password = newPassword;
}

// UserManager class implementation
UserManager::UserManager() {
    loadUsers();
}

User* UserManager::login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end() && it->second->getPassword() == password) {
        return it->second;
    }
    return nullptr;
}

void UserManager::registerUser(const std::string& username, const std::string& password, User::UserType type) {
    if (users.find(username) == users.end()) {
        users[username] = new User(username, password, type);
        saveUsers();
        std::cout << "用户 " << username << " 注册成功！" << std::endl;
    } else {
        std::cout << "用户 " << username << " 已存在。" << std::endl;
    }
}

void UserManager::saveUsers() {
    nlohmann::json j;
    for (const auto& pair : users) {
        nlohmann::json userJson;
        userJson["username"] = pair.second->getUsername();
        userJson["password"] = pair.second->getPassword();
        userJson["type"] = pair.second->getUserType();

        if (pair.second->getUserType() == User::PLAYER) {
            nlohmann::json saveSlotsJson = nlohmann::json::array();
            for (const auto& slot : pair.second->saveSlots) {
                nlohmann::json pokemonListJson = nlohmann::json::array();
                for (const auto& pokemon : slot) {
                    pokemonListJson.push_back(pokemon.toJson());
                }
                saveSlotsJson.push_back(pokemonListJson);
            }
            userJson["saveSlots"] = saveSlotsJson;
        }
        j[pair.first] = userJson;
    }

    std::ofstream ofs(getUserDataFilePath());
    if (ofs.is_open()) {
        ofs << j.dump(4);
        ofs.close();
    } else {
        std::cerr << "无法保存用户数据到文件: " << getUserDataFilePath() << std::endl;
    }
}

void UserManager::loadUsers() {
    std::ifstream ifs(getUserDataFilePath());
    if (ifs.is_open()) {
        nlohmann::json j;
        ifs >> j;
        ifs.close();

        for (auto it = j.begin(); it != j.end(); ++it) {
            std::string username = it.key();
            std::string password = it.value()["password"];
            User::UserType type = it.value()["type"];
            User* user = new User(username, password, type);

            if (type == User::PLAYER) {
                if (it.value().contains("saveSlots")) {
                    for (const auto& slotJson : it.value()["saveSlots"]) {
                        std::vector<Pokemon> pokemonList;
                        for (const auto& pokemonJson : slotJson) {
                            pokemonList.push_back(Pokemon::fromJson(pokemonJson));
                        }
                        user->saveSlots.push_back(pokemonList);
                    }
                }
            }
            users[username] = user;
        }
    } else {
        std::cout << "用户数据文件不存在，将创建新文件。" << std::endl;
    }
}

void UserManager::createUser(const std::string& username, const std::string& password, User::UserType type) {
    registerUser(username, password, type);
}

void UserManager::deleteUser(const std::string& username) {
    auto it = users.find(username);
    if (it != users.end()) {
        delete it->second; // Free memory
        users.erase(it);
        saveUsers();
        std::cout << "用户 " << username << " 已删除。" << std::endl;
    } else {
        std::cout << "用户 " << username << " 不存在。" << std::endl;
    }
}

void UserManager::updateUserPassword(const std::string& username, const std::string& newPassword) {
    auto it = users.find(username);
    if (it != users.end()) {
        it->second->setPassword(newPassword);
        saveUsers();
        std::cout << "用户 " << username << " 的密码已更新。" << std::endl;
    } else {
        std::cout << "用户 " << username << " 不存在。" << std::endl;
    }
}

void UserManager::listAllUsers() const {
    std::cout << "所有用户:" << std::endl;
    for (const auto& pair : users) {
        std::cout << "- 用户名: " << pair.second->getUsername()
                  << ", 类型: " << (pair.second->getUserType() == User::PLAYER ? "玩家" : "管理员") << std::endl;
    }
}

User* UserManager::getUserByUsername(const std::string& username) const {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second;
    }
    return nullptr;
}

std::string UserManager::getUserDataFilePath() const {
    return "users.json"; // Or a more robust path like in a data directory
}
