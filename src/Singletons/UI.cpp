/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午2:14
* @version: 1.0
* @description: 
*******************************************************************************/
#include <string>
#include <iostream>
#include "../../include/Singletons/UI.h"
#include "../../include/Singletons/Game.h"
#include "../../include/Singletons/UserManager.h"


void UI::showLoginScreen()
{
    std::string username, password;
    int choice;

    while (true)
    {
        std::cout << "\n--- 登录/注册 ---" << std::endl;
        std::cout << "1. 登录" << std::endl;
        std::cout << "2. 注册" << std::endl;
        std::cout << "3. 退出游戏" << std::endl;
        std::cout << "请输入您的选择: \n";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "无效输入，请重新输入数字。" << std::endl;
            std::cin.clear();
            Game::GetInstance().clearInputBuffer();
            continue;
        }
        Game::GetInstance().clearInputBuffer();

        if (choice == 1)
        {
            std::cout << "请输入用户名: \n";
            std::getline(std::cin, username);
            std::cout << "请输入密码: \n";
            std::getline(std::cin, password);

            Game::GetInstance().currentUser = UserManager::GetInstance().login(username, password);
            if (Game::GetInstance().currentUser)
            {
                std::cout << "登录成功！" << std::endl;
                if (Game::GetInstance().currentUser->getUserType() == User::ADMIN)
                {
                    showAdminMenu();
                }
                else
                {
                    // Check if it's a new player (no saved games)
                    bool newPlayer = true;
                    for (const auto &slot: Game::GetInstance().currentUser->saveSlots)
                    {
                        if (!slot.empty())
                        {
                            newPlayer = false;
                            break;
                        }
                    }

                    if (newPlayer)
                    {
                        std::cout << "欢迎新玩家！请选择你的初始宝可梦："
                                  << std::endl;
                        std::cout << "1. 火属性" << std::endl;
                        std::cout << "2. 草属性" << std::endl;
                        std::cout << "3. 冰属性" << std::endl;
                        int pokemonChoice;
                        while (true)
                        {
                            std::cout << "请输入选择 (1-3): ";
                            std::cin >> pokemonChoice;
                            if (std::cin.fail() || pokemonChoice < 1 ||
                                pokemonChoice > 3)
                            {
                                std::cout << "无效选择，请重新输入。"
                                          << std::cin.fail() << std::endl;
                                std::cin.clear();
                                Game::GetInstance().clearInputBuffer();
                            }
                            else
                            {
                                Game::GetInstance().clearInputBuffer();
                                break;
                            }
                        }

                        Pokemon::Type initialType;
                        switch (pokemonChoice)
                        {
                            case 1:
                                initialType = Pokemon::FIRE;
                                break;
                            case 2:
                                initialType = Pokemon::GRASS;
                                break;
                            case 3:
                                initialType = Pokemon::ICE;
                                break;
                            default:
                                initialType = Pokemon::FIRE;
                                break; // Should not happen
                        }
                        Game::GetInstance().currentUser->saveSlots[0].push_back(
                                Pokemon(initialType));
                        std::cout << "你选择了 "
                                  << Game::GetInstance().currentUser->saveSlots[0][0].name
                                  << " 作为你的初始宝可梦！" << std::endl;
                        Game::GetInstance().playerActivePokemon = std::make_shared<Pokemon>(Game::GetInstance().currentUser->saveSlots[0][0]); // Set initial active Pokemon
                        showPlayerMainMenu();
                    }
                    else
                    {
                        showSaveLoadMenu();
                    }
                }
                break; // Exit login loop on successful login
            }
            else
            {
                std::cout << "用户名或密码错误，请重试。" << std::endl;
            }
        }
        else if (choice == 2)
        {
            std::cout << "请输入新用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入新密码: ";
            std::getline(std::cin, password);
            UserManager::GetInstance().registerUser(username, password, User::PLAYER);
        }
        else if (choice == 3)
        {
            std::cout << "感谢游玩，再见！" << std::endl;
            exit(0);
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void UI::showAdminMenu()
{
    std::string input;
    while (true)
    {
        std::cout << "\n--- 管理员菜单 ---" << std::endl;
        std::cout << "1. 创建用户" << std::endl;
        std::cout << "2. 删除用户" << std::endl;
        std::cout << "3. 更新用户密码" << std::endl;
        std::cout << "4. 列出所有用户" << std::endl;
        std::cout << "exit. 返回登录界面" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input == "1")
        {
            std::string username, password, typeStr;
            User::UserType type;
            std::cout << "请输入新用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入密码: ";
            std::getline(std::cin, password);
            while (true)
            {
                std::cout << "请输入用户类型 (player/admin): ";
                std::getline(std::cin, typeStr);
                if (typeStr == "player")
                {
                    type = User::PLAYER;
                    break;
                }
                else if (typeStr == "admin")
                {
                    type = User::ADMIN;
                    break;
                }
                else
                { std::cout << "无效类型，请重新输入。" << std::endl; }
            }
            UserManager::GetInstance().createUser(username, password, type);
        }
        else if (input == "2")
        {
            std::string username;
            std::cout << "请输入要删除的用户名: ";
            std::getline(std::cin, username);
            UserManager::GetInstance().deleteUser(username);
        }
        else if (input == "3")
        {
            std::string username, newPassword;
            std::cout << "请输入要更新密码的用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入新密码: ";
            std::getline(std::cin, newPassword);
            UserManager::GetInstance().updateUserPassword(username, newPassword);
        }
        else if (input == "4")
        {
            UserManager::GetInstance().listAllUsers();
        }
        else if (input == "exit")
        {
            Game::GetInstance().currentUser = nullptr;
            showLoginScreen();
            break;
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void UI::showPlayerMainMenu()
{
    std::string input;
    while (true)
    {
        std::cout << "\n--- 主菜单 ---" << std::endl;
        std::cout << "输入 p 查看所有宝可梦" << std::endl;
        std::cout << "输入 f 进入战斗" << std::endl;
        std::cout << "输入 s 存档" << std::endl;
        std::cout << "输入 exit 退出到登录界面" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input == "p")
        {
            showPokemonManagementMenu();
        }
        else if (input == "f")
        {
            Game::GetInstance().startBattle();
        }
        else if (input == "s")
        {
            showSaveLoadMenu();
        }
        else if (input == "exit")
        {
            Game::GetInstance().currentUser = nullptr;
            showLoginScreen();
            break;
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void UI::showSaveLoadMenu()
{
    std::string input;
    while (true)
    {
        std::cout << "\n--- 存档菜单 ---" << std::endl;
        for (size_t i = 0; i < Game::GetInstance().currentUser->saveSlots.size(); ++i)
        {
            std::cout << (i + 1) << ". 存档槽位 " << (i + 1)
                      << (Game::GetInstance().currentUser->saveSlots[i].empty() ? " (空)"
                                                            : " (有数据)")
                      << std::endl;
        }
        std::cout << "输入 load [槽位号] 载入存档" << std::endl;
        std::cout << "输入 save [槽位号] 保存存档" << std::endl;
        std::cout << "输入 exit 返回主菜单" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input.rfind("load ", 0) == 0)
        { // Check if input starts with "load "
            int slotIndex = std::stoi(input.substr(5)) - 1;
            if (slotIndex >= 0 && slotIndex < Game::GetInstance().currentUser->saveSlots.size())
            {
                Game::GetInstance().loadPlayerSave(std::make_shared<User>(*(Game::GetInstance().currentUser)), slotIndex);
            }
            else
            {
                std::cout << "无效的槽位号。" << std::endl;
            }
        }
        else if (input.rfind("save ", 0) == 0)
        { // Check if input starts with "save "
            int slotIndex = std::stoi(input.substr(5)) - 1;
            if (slotIndex >= 0 && slotIndex < Game::GetInstance().currentUser->saveSlots.size())
            {
                Game::GetInstance().savePlayerSave(std::make_shared<User>(*(Game::GetInstance().currentUser)), slotIndex);
            }
            else
            {
                std::cout << "无效的槽位号。" << std::endl;
            }
        }
        else if (input == "exit")
        {
            break;
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void UI::showPokemonManagementMenu()
{
    std::string input;
    if (!Game::GetInstance().playerActivePokemon)
    {
        std::cout << "请先选择一个出战宝可梦。" << std::endl;
        Game::GetInstance().selectActivePokemon(
                Game::GetInstance().currentUser->saveSlots[0]); // Assuming slot 0 is the current game
        if (!Game::GetInstance().playerActivePokemon) return; // If still no active Pokemon, return
    }

    while (true)
    {
        std::cout << "\n--- 宝可梦管理 ---" << std::endl;
        displayAllPokemon(
                Game::GetInstance().currentUser->saveSlots[0]); // Display Pokemon from the current save slot
        std::cout << "当前出战宝可梦: "
                  << (Game::GetInstance().playerActivePokemon ? Game::GetInstance().playerActivePokemon->name : "无")
                  << std::endl;
        std::cout << "输入 [宝可梦ID] 选择出战宝可梦" << std::endl;
        std::cout << "输入 A1 [宝可梦ID] 装备防具" << std::endl;
        std::cout << "输入 A2 [宝可梦ID] 卸下防具" << std::endl;
        std::cout << "输入 D1 [宝可梦ID] 装备饰品" << std::endl;
        std::cout << "输入 D2 [宝可梦ID] 卸下饰品" << std::endl;
        std::cout << "输入 exit 返回主菜单" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input == "exit")
        {
            break;
        }
        else if (input.rfind("A1 ", 0) == 0)
        {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < Game::GetInstance().currentUser->saveSlots[0].size())
            {
                auto& pokemon = Game::GetInstance().currentUser->saveSlots[0][pokemonId];
                Game::GetInstance().equipPokemon(EquipType::Armor, pokemon);
            }
            else
            {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        }
        else if (input.rfind("A2 ", 0) == 0)
        {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < Game::GetInstance().currentUser->saveSlots[0].size())
            {
                auto& pokemon = Game::GetInstance().currentUser->saveSlots[0][pokemonId];
                Game::GetInstance().unequipPokemon(EquipType::Armor, pokemon);
            }
            else
            {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        }
        else if (input.rfind("D1 ", 0) == 0)
        {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < Game::GetInstance().currentUser->saveSlots[0].size())
            {
                auto& pokemon = Game::GetInstance().currentUser->saveSlots[0][pokemonId];
                Game::GetInstance().equipPokemon(EquipType::Accessory, pokemon); // Re-using equip for accessory
            }
            else
            {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        }
        else if (input.rfind("D2 ", 0) == 0)
        {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < Game::GetInstance().currentUser->saveSlots[0].size())
            {
                auto &pokemon = Game::GetInstance().currentUser->saveSlots[0][pokemonId];
                Game::GetInstance().unequipPokemon(EquipType::Accessory, pokemon); // Re-using unequip for accessory
            }
            else
            {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        }
        else
        {
            try
            {
                int pokemonId = std::stoi(input) - 1;
                if (pokemonId >= 0 &&
                    pokemonId < Game::GetInstance().currentUser->saveSlots[0].size())
                {
                    Game::GetInstance().playerActivePokemon = std::make_shared<Pokemon>(Game::GetInstance().currentUser->saveSlots[0][pokemonId]);
                    std::cout << "已选择 " << Game::GetInstance().playerActivePokemon->name
                              << " 作为出战宝可梦。" << std::endl;
                }
                else
                {
                    std::cout << "无效的宝可梦ID。" << std::endl;
                }
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "无效选择，请重新输入。" << std::endl;
            }
        }
    }
}

void UI::displayAllPokemon(const std::vector<Pokemon> &pokemonList) const
{
    if (pokemonList.empty())
    {
        std::cout << "你还没有任何宝可梦。" << std::endl;
        return;
    }
    std::cout << "\n--- 你的宝可梦 ---" << std::endl;
    for (size_t i = 0; i < pokemonList.size(); ++i)
    {
        std::cout << "ID: " << (i + 1) << std::endl;
        pokemonList[i].displayStats();
    }
}

void UI::displayBattleStatus() const
{
    std::cout << "\n--- 战斗状态 ---" << std::endl;
    std::cout << "你的宝可梦: " << Game::GetInstance().playerActivePokemon->name << " (HP: "
              << Game::GetInstance().playerActivePokemon->currentHealth << "/"
              << Game::GetInstance().playerActivePokemon->maxHealth << ", MP: "
              << Game::GetInstance().playerActivePokemon->currentMagic << "/"
              << Game::GetInstance().playerActivePokemon->maxMagic << ")" << std::endl;
    std::cout << "敌方宝可梦: " << Game::GetInstance().enemyActivePokemon->name << " (HP: "
              << Game::GetInstance().enemyActivePokemon->currentHealth << "/"
              << Game::GetInstance().enemyActivePokemon->maxHealth << ")" << std::endl;
    std::cout << "--------------------" << std::endl;
}

