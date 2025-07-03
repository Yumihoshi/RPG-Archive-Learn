/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午2:27
* @version: 1.0
* @description: 
*******************************************************************************/
#include <iostream>
#include <fstream>
#include "../../include/Singletons/UserManager.h"
#include "../../include/Singletons/PokemonFactory.h"
#include "../../include/Equip/Accessory.h"
#include "../../include/Equip/Armor.h"


// UserManager class implementation
UserManager::UserManager()
{
    loadUsers();
}

std::shared_ptr<User>
UserManager::login(const std::string &username, const std::string &password)
{
    auto it = users.find(username);
    if (it != users.end() && it->second->getPassword() == password)
    {
        return it->second;
    }
    return nullptr;
}

void UserManager::registerUser(const std::string &username,
                               const std::string &password, User::UserType type)
{
    if (username.empty())
    {
        std::cout << "用户名不能为空。" << std::endl;
        return;
    }
    if (password.empty())
    {
        std::cout << "密码不能为空。" << std::endl;
        return;
    }
    if (users.find(username) == users.end())
    {
        users[username] = std::make_shared<User>(username, password, type);
        saveUsers();
        std::cout << "用户 " << username << " 注册成功！" << std::endl;
    }
    else
    {
        std::cout << "用户 " << username << " 已存在。" << std::endl;
    }
}

void UserManager::saveUsers()
{
    nlohmann::json j;
    for (const auto &pair: users)
    {
        nlohmann::json userJson;
        userJson["username"] = pair.second->getUsername();
        userJson["password"] = pair.second->getPassword();
        userJson["type"] = pair.second->getUserType();

        if (pair.second->getUserType() == User::PLAYER)
        {
            nlohmann::json saveSlotsJson = nlohmann::json::array();
            for (const auto &slot: pair.second->saveSlots)
            {
                nlohmann::json pokemonListJson = nlohmann::json::array();
                for (const auto &pokemon: slot)
                {
                    pokemonListJson.push_back(pokemon->toJson());
                }
                saveSlotsJson.push_back(pokemonListJson);
            }
            userJson["saveSlots"] = saveSlotsJson;
        }
        j[pair.first] = userJson;
    }

    std::ofstream ofs(getUserDataFilePath());
    if (ofs.is_open())
    {
        ofs << j.dump(4);
        ofs.close();
    }
    else
    {
        std::cerr << "无法保存用户数据到文件: " << getUserDataFilePath()
                  << std::endl;
    }
}

void UserManager::loadUsers()
{
    std::ifstream ifs(getUserDataFilePath());
    if (ifs.is_open())
    {
        nlohmann::json j;
        ifs >> j;
        ifs.close();

        for (auto it = j.begin(); it != j.end(); ++it)
        {
            std::string username = it.key();
            std::string password = it.value()["password"];
            User::UserType type = it.value()["type"];
            std::shared_ptr<User> user = std::make_shared<User>(username,
                                                                password, type);

            if (type == User::PLAYER)
            {
                if (it.value().contains("saveSlots"))
                {
                    int slotIndex = 0;
                    for (const auto &slotJson: it.value()["saveSlots"])
                    {
                        if (slotIndex < user->saveSlots.size()) {
                            std::vector<std::shared_ptr<Pokemon>> pokemonList;
                            for (const auto &pokemonJson: slotJson)
                            {
                                pokemonList.push_back(
                                        PokemonFactory::createPokemon(pokemonJson));
                            }
                            user->saveSlots[slotIndex] = pokemonList;
                        } else {
                            // Handle case where saveSlots has more entries than expected (e.g., corrupted file)
                            std::cerr << "警告: 存档槽位索引超出范围，跳过加载。" << std::endl;
                        }
                        slotIndex++;
                    }
                }
            }
            users[username] = user;
        }
    }
    else
    {
        std::cout << "用户数据文件不存在，将创建新文件。" << std::endl;
    }
}

void UserManager::createUser(const std::string &username,
                             const std::string &password, User::UserType type)
{
    registerUser(username, password, type);
}

void UserManager::deleteUser(const std::string &username)
{
    auto it = users.find(username);
    if (it != users.end())
    {
        users.erase(it);
        saveUsers();
        std::cout << "用户 " << username << " 已删除。" << std::endl;
    }
    else
    {
        std::cout << "用户 " << username << " 不存在。" << std::endl;
    }
}

void UserManager::updateUserPassword(const std::string &username,
                                     const std::string &newPassword)
{
    auto it = users.find(username);
    if (it != users.end())
    {
        it->second->setPassword(newPassword);
        saveUsers();
        std::cout << "用户 " << username << " 的密码已更新。" << std::endl;
    }
    else
    {
        std::cout << "用户 " << username << " 不存在。" << std::endl;
    }
}

void UserManager::listAllUsers() const
{
    std::cout << "所有用户:" << std::endl;
    for (const auto &pair: users)
    {
        std::cout << "- 用户名: " << pair.second->getUsername()
                  << ", 类型: "
                  << (pair.second->getUserType() == User::PLAYER ? "玩家"
                                                                 : "管理员")
                  << std::endl;
    }
}

std::shared_ptr<User>
UserManager::getUserByUsername(const std::string &username) const
{
    auto it = users.find(username);
    if (it != users.end())
    {
        return it->second;
    }
    return nullptr;
}

std::string UserManager::getUserDataFilePath() const
{
    return "users.json"; // Or a more robust path like in a data directory
}

void UserManager::equipPokemonAccessory(const std::string &username,
                                        int saveSlotIndex, int pokemonIndex,
                                        std::shared_ptr<Accessory> accessory)
{
    auto user = getUserByUsername(username);
    if (!user || user->getUserType() != User::PLAYER)
    {
        std::cout << "用户不存在或不是玩家。" << std::endl;
        return;
    }

    if (saveSlotIndex < 0 || saveSlotIndex >= user->saveSlots.size())
    {
        std::cout << "无效的存档槽位。" << std::endl;
        return;
    }

    if (pokemonIndex < 0 ||
        pokemonIndex >= user->saveSlots[saveSlotIndex].size())
    {
        std::cout << "无效的宝可梦索引。" << std::endl;
        return;
    }

    auto pokemon = user->saveSlots[saveSlotIndex][pokemonIndex];
    if (pokemon->accessory)
    {
        pokemon->accessory->removeEffect(pokemon);
    }
    pokemon->accessory = accessory;
    if (accessory)
    {
        accessory->applyEffect(pokemon);
    }
    saveUsers();
    std::cout << pokemon->name << " 装备了饰品 " << accessory->name << std::endl;
}

void UserManager::unequipPokemonAccessory(const std::string &username,
                                          int saveSlotIndex, int pokemonIndex)
{
    auto user = getUserByUsername(username);
    if (!user || user->getUserType() != User::PLAYER)
    {
        std::cout << "用户不存在或不是玩家。" << std::endl;
        return;
    }

    if (saveSlotIndex < 0 || saveSlotIndex >= user->saveSlots.size())
    {
        std::cout << "无效的存档槽位。" << std::endl;
        return;
    }

    if (pokemonIndex < 0 ||
        pokemonIndex >= user->saveSlots[saveSlotIndex].size())
    {
        std::cout << "无效的宝可梦索引。" << std::endl;
        return;
    }

    auto pokemon = user->saveSlots[saveSlotIndex][pokemonIndex];
    if (pokemon->accessory)
    {
        pokemon->accessory->removeEffect(pokemon);
        std::cout << pokemon->name << " 卸下了饰品 " << pokemon->accessory->name
                  << std::endl;
        pokemon->accessory = nullptr;
        saveUsers();
    }
    else
    {
        std::cout << pokemon->name << " 没有装备饰品。" << std::endl;
    }
}

void UserManager::equipPokemonArmor(const std::string &username,
                                    int saveSlotIndex, int pokemonIndex,
                                    std::shared_ptr<Armor> armor)
{
    auto user = getUserByUsername(username);
    if (!user || user->getUserType() != User::PLAYER)
    {
        std::cout << "用户不存在或不是玩家。" << std::endl;
        return;
    }

    if (saveSlotIndex < 0 || saveSlotIndex >= user->saveSlots.size())
    {
        std::cout << "无效的存档槽位。" << std::endl;
        return;
    }

    if (pokemonIndex < 0 ||
        pokemonIndex >= user->saveSlots[saveSlotIndex].size())
    {
        std::cout << "无效的宝可梦索引。" << std::endl;
        return;
    }

    auto pokemon = user->saveSlots[saveSlotIndex][pokemonIndex];
    if (pokemon->armor)
    {
        pokemon->armor->removeEffect(pokemon);
    }
    pokemon->armor = armor;
    if (armor)
    {
        armor->applyEffect(pokemon);
    }
    saveUsers();
    std::cout << pokemon->name << " 装备了防具 " << armor->name << std::endl;
}

void UserManager::unequipPokemonArmor(const std::string &username,
                                       int saveSlotIndex, int pokemonIndex)
{
    auto user = getUserByUsername(username);
    if (!user || user->getUserType() != User::PLAYER)
    {
        std::cout << "用户不存在或不是玩家。" << std::endl;
        return;
    }

    if (saveSlotIndex < 0 || saveSlotIndex >= user->saveSlots.size())
    {
        std::cout << "无效的存档槽位。" << std::endl;
        return;
    }

    if (pokemonIndex < 0 ||
        pokemonIndex >= user->saveSlots[saveSlotIndex].size())
    {
        std::cout << "无效的宝可梦索引。" << std::endl;
        return;
    }

    auto pokemon = user->saveSlots[saveSlotIndex][pokemonIndex];
    if (pokemon->armor)
    {
        pokemon->armor->removeEffect(pokemon);
        std::cout << pokemon->name << " 卸下了防具 " << pokemon->armor->name
                  << std::endl;
        pokemon->armor = nullptr;
        saveUsers();
    }
    else
    {
        std::cout << pokemon->name << " 没有装备防具。" << std::endl;
    }
}

void UserManager::listPokemonEquipment(const std::string &username,
                                       int saveSlotIndex, int pokemonIndex) const
{
    auto user = getUserByUsername(username);
    if (!user || user->getUserType() != User::PLAYER)
    {
        std::cout << "用户不存在或不是玩家。" << std::endl;
        return;
    }

    if (saveSlotIndex < 0 || saveSlotIndex >= user->saveSlots.size())
    {
        std::cout << "无效的存档槽位。" << std::endl;
        return;
    }

    if (pokemonIndex < 0 ||
        pokemonIndex >= user->saveSlots[saveSlotIndex].size())
    {
        std::cout << "无效的宝可梦索引。" << std::endl;
        return;
    }

    auto pokemon = user->saveSlots[saveSlotIndex][pokemonIndex];
    std::cout << pokemon->name << " 的装备:" << std::endl;
    if (pokemon->accessory)
    {
        std::cout << "  饰品: " << pokemon->accessory->name << std::endl;
    }
    else
    {
        std::cout << "  饰品: 无" << std::endl;
    }
    if (pokemon->armor)
    {
        std::cout << "  防具: " << pokemon->armor->name << std::endl;
    }
    else
    {
        std::cout << "  防具: 无" << std::endl;
    }
}
