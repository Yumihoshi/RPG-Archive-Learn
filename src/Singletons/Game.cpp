#include <iostream>
#include <limits>
#include <random>
#include <algorithm>
#include "../../include/Singletons/Game.h"
#include "../../include/Equip/Equipment.h"
#include "../../include/Equip/Armor.h"
#include "../../include/Equip/Accessory.h"
#include "../../include/Singletons/UI.h"
#include "../../include/Singletons/UserManager.h"

#include "../../include/Singletons/PokemonFactory.h"
#include "../../include/Common/Types.h"

// 清除输入缓冲区
void Game::clearInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Game::Game() : currentUser(nullptr), playerActivePokemon(nullptr),
               enemyActivePokemon(nullptr)
{
    // 初始化用户管理器
}

void Game::run()
{
    loginMenu();
}

void Game::loginMenu()
{
    std::string username, password, choice;
    while (true)
    {
        std::cout << "\n--- 登录/注册 ---" << std::endl;
        std::cout << "1. 登录" << std::endl;
        std::cout << "2. 注册" << std::endl;
        std::cout << "3. 退出" << std::endl;
        std::cout << "请输入你的选择: ";
        std::cin >> choice;
        clearInputBuffer();

        if (choice == "1")
        {
            std::cout << "请输入用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入密码: ";
            std::getline(std::cin, password);

            currentUser = UserManager::GetInstance().login(username, password);
            if (currentUser)
            {
                std::cout << "登录成功！欢迎，" << currentUser->getUsername()
                          << "！"
                          << std::endl;
                if (currentUser->getUserType() == User::ADMIN)
                {
                    adminMenu();
                }
                else
                {
                    // 检查是否是新玩家
                    bool isNewPlayer = true;
                    for (const auto &slot: currentUser->saveSlots)
                    {
                        if (!slot.empty())
                        {
                            isNewPlayer = false;
                            break;
                        }
                    }

                    if (isNewPlayer)
                    {
                        std::cout << "检测到您是第一次游玩，请选择您的初始宝可梦。"
                                  << std::endl;
                        chooseInitialPokemon(currentUser);
                    }
                    playerMainMenu();
                }
                break;
            }
            else
            {
                std::cout << "用户名或密码错误，请重试。" << std::endl;
            }
        }
        else if (choice == "2")
        {
            std::cout << "请输入新用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入新密码: ";
            std::getline(std::cin, password);
            UserManager::GetInstance().registerUser(username, password,
                                                    User::PLAYER);
        }
        else if (choice == "3")
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

void Game::adminMenu()
{
    std::string choice;
    std::string username, password;
    User::UserType type;
    while (true)
    {
        std::cout << "\n--- 管理员菜单 ---" << std::endl;
        std::cout << "1. 创建用户" << std::endl;
        std::cout << "2. 删除用户" << std::endl;
        std::cout << "3. 更新用户密码" << std::endl;
        std::cout << "4. 列出所有用户" << std::endl;
        std::cout << "5. 按用户名搜索用户" << std::endl;
        std::cout << "6. 查看用户存档" << std::endl;
        std::cout << "7. 管理用户宝可梦" << std::endl;
        std::cout << "8. 管理用户宝可梦装备" << std::endl;
        std::cout << "9. 返回登录界面" << std::endl;
        std::cout << "请输入你的选择: ";
        std::cin >> choice;
        clearInputBuffer();

        if (choice == "1")
        {
            std::cout << "请输入用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入密码: ";
            std::getline(std::cin, password);
            std::cout << "请输入用户类型 (0: 玩家, 1: 管理员): ";
            int userTypeChoice;
            std::cin >> userTypeChoice;
            clearInputBuffer();
            type = static_cast<User::UserType>(userTypeChoice);
            UserManager::GetInstance().createUser(username, password, type);
        }
        else if (choice == "2")
        {
            std::cout << "请输入要删除的用户名: ";
            std::getline(std::cin, username);
            UserManager::GetInstance().deleteUser(username);
        }
        else if (choice == "3")
        {
            std::cout << "请输入要更新密码的用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入新密码: ";
            std::getline(std::cin, password);
            UserManager::GetInstance().updateUserPassword(username, password);
        }
        else if (choice == "4")
        {
            UserManager::GetInstance().listAllUsers();
        }
        else if (choice == "5")
        {
            std::cout << "请输入要搜索的用户名: ";
            std::getline(std::cin, username);
            // 新增用户查询逻辑
            auto user = UserManager::GetInstance().getUserByUsername(username);
            if(user) {
                std::cout << "找到用户: " << user->getUsername()
                          << ", 类型: "
                          << (user->getUserType() == User::PLAYER ? "玩家" : "管理员")
                          << std::endl;
            } else {
                std::cout << "用户 " << username << " 不存在。" << std::endl;
            }
        }
        else if (choice == "6")
        {
            adminViewUserSave();
        }
        else if (choice == "7")
        {
            adminManageUserPokemon();
        }
        else if (choice == "8")
        {
            adminManageUserPokemonEquipment();
        }
        else if (choice == "9" || choice == "exit")
        {
            break;
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::adminViewUserSave()
{
    std::string username;
    std::cout << "请输入要查看存档的用户名: ";
    std::getline(std::cin, username);

    std::shared_ptr<User> user = UserManager::GetInstance().getUserByUsername(
            username);
    if (user && user->getUserType() == User::PLAYER)
    {
        std::cout << "\n--- 用户 " << username << " 的存档 ---" << std::endl;
        for (size_t i = 0; i < user->saveSlots.size(); ++i)
        {
            std::cout << "存档槽位 " << (i + 1) << ": ";
            if (user->saveSlots[i].empty())
            {
                std::cout << "空" << std::endl;
            }
            else
            {
                std::cout << user->saveSlots[i].size() << " 只宝可梦"
                          << std::endl;
                UI::GetInstance().displayAllPokemon(user->saveSlots[i]);
            }
        }
    }
    else
    {
        std::cout << "用户 " << username << " 不存在或不是玩家。" << std::endl;
    }
}

void Game::adminManageUserPokemon()
{
    std::string username;
    std::cout << "请输入要管理宝可梦的用户名: ";
    std::getline(std::cin, username);

    std::shared_ptr<User> user = UserManager::GetInstance().getUserByUsername(
            username);
    if (user && user->getUserType() == User::PLAYER)
    {
        std::string choice;
        while (true)
        {
            std::cout << "\n--- 管理用户 " << username << " 的宝可梦 ---"
                      << std::endl;
            std::cout << "1. 查看所有宝可梦" << std::endl;
            std::cout << "2. 添加宝可梦" << std::endl;
            std::cout << "3. 删除宝可梦" << std::endl;
            std::cout << "4. 返回" << std::endl;
            std::cout << "请输入你的选择: ";
            std::cin >> choice;
            clearInputBuffer();

            if (choice == "1")
            {
                UI::GetInstance().displayAllPokemon(
                        user->saveSlots[0]); // Assuming managing slot 0
            }
            else if (choice == "2")
            {
                std::cout
                        << "请输入要添加的宝可梦类型 (0: 火, 1: 草, 2: 冰, 3: 飞行, 4: 幽灵): ";
                int typeChoice;
                std::cin >> typeChoice;
                clearInputBuffer();
                if (typeChoice >= 0 && typeChoice <= 4)
                {
                    user->saveSlots[0].push_back(PokemonFactory::createPokemon(
                            static_cast<Pokemon::PokeType>(typeChoice)));
                    UserManager::GetInstance().saveUsers();
                    std::cout << "宝可梦添加成功！" << std::endl;
                }
                else
                {
                    std::cout << "无效的宝可梦类型。" << std::endl;
                }
            }
            else if (choice == "3")
            {
                std::cout << "请输入要删除的宝可梦ID: ";
                int pokemonId;
                std::cin >> pokemonId;
                clearInputBuffer();
                if (pokemonId > 0 && pokemonId <= user->saveSlots[0].size())
                {
                    user->saveSlots[0].erase(
                            user->saveSlots[0].begin() + pokemonId - 1);
                    UserManager::GetInstance().saveUsers();
                    std::cout << "宝可梦删除成功！" << std::endl;
                }
                else
                {
                    std::cout << "无效的宝可梦ID。" << std::endl;
                }
            }
            else if (choice == "4" || choice == "exit")
            {
                break;
            }
            else
            {
                std::cout << "无效选择，请重新输入。" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "用户 " << username << " 不存在或不是玩家。" << std::endl;
    }
}

void Game::adminManageUserPokemonEquipment()
{
    std::string username;
    std::cout << "请输入要管理宝可梦装备的用户名: ";
    std::getline(std::cin, username);

    std::shared_ptr<User> user = UserManager::GetInstance().getUserByUsername(
            username);
    if (user && user->getUserType() == User::PLAYER)
    {
        std::string choice;
        while (true)
        {
            std::cout << "\n--- 管理用户 " << username << " 的宝可梦装备 ---"
                      << std::endl;
            std::cout << "1. 查看宝可梦装备" << std::endl;
            std::cout << "2. 装备饰品" << std::endl;
            std::cout << "3. 卸下饰品" << std::endl;
            std::cout << "4. 装备防具" << std::endl;
            std::cout << "5. 卸下防具" << std::endl;
            std::cout << "6. 返回" << std::endl;
            std::cout << "请输入你的选择: ";
            std::cin >> choice;
            clearInputBuffer();

            if (choice == "1")
            {
                UI::GetInstance().displayAllPokemon(user->saveSlots[0]);
                std::cout << "请输入要查看装备的宝可梦ID: ";
                int pokemonId;
                std::cin >> pokemonId;
                clearInputBuffer();
                if (pokemonId > 0 && pokemonId <= user->saveSlots[0].size())
                {
                    UserManager::GetInstance().listPokemonEquipment(
                            username, 0, pokemonId - 1);
                }
                else
                {
                    std::cout << "无效宝可梦ID。" << std::endl;
                }
            }
            else if (choice == "2")
            {
                UI::GetInstance().displayAllPokemon(user->saveSlots[0]);
                std::cout << "请输入要装备饰品的宝可梦ID: ";
                int pokemonId;
                std::cin >> pokemonId;
                clearInputBuffer();
                if (pokemonId > 0 && pokemonId <= user->saveSlots[0].size())
                {
                    std::string accessoryName;
                    int attackBonus, magicBonus;
                    double criticalRateBonus;
                    std::cout << "请输入饰品名称: ";
                    std::getline(std::cin, accessoryName);
                    std::cout << "请输入攻击加成: ";
                    std::cin >> attackBonus;
                    std::cout << "请输入魔法加成: ";
                    std::cin >> magicBonus;
                    std::cout << "请输入暴击率加成 (例如: 0.05): ";
                    std::cin >> criticalRateBonus;
                    clearInputBuffer();
                    std::shared_ptr<Accessory> newAccessory = std::make_shared<Accessory>(
                            accessoryName, attackBonus, magicBonus,
                            criticalRateBonus);
                    UserManager::GetInstance().equipPokemonAccessory(
                            username, 0, pokemonId - 1, newAccessory);
                }
                else
                {
                    std::cout << "无效宝可梦ID。" << std::endl;
                }
            }
            else if (choice == "3")
            {
                UI::GetInstance().displayAllPokemon(user->saveSlots[0]);
                std::cout << "请输入要卸下饰品的宝可梦ID: ";
                int pokemonId;
                std::cin >> pokemonId;
                clearInputBuffer();
                if (pokemonId > 0 && pokemonId <= user->saveSlots[0].size())
                {
                    UserManager::GetInstance().unequipPokemonAccessory(
                            username, 0, pokemonId - 1);
                }
                else
                {
                    std::cout << "无效宝可梦ID。" << std::endl;
                }
            }
            else if (choice == "4")
            {
                UI::GetInstance().displayAllPokemon(user->saveSlots[0]);
                std::cout << "请输入要装备防具的宝可梦ID: ";
                int pokemonId;
                std::cin >> pokemonId;
                clearInputBuffer();
                if (pokemonId > 0 && pokemonId <= user->saveSlots[0].size())
                {
                    std::string armorName;
                    int healthBonus;
                    double evasionRateBonus;
                    std::cout << "请输入防具名称: ";
                    std::getline(std::cin, armorName);
                    std::cout << "请输入生命值加成: ";
                    std::cin >> healthBonus;
                    std::cout << "请输入闪避率加成 (例如: 0.02): ";
                    std::cin >> evasionRateBonus;
                    clearInputBuffer();
                    std::shared_ptr<Armor> newArmor = std::make_shared<Armor>(
                            armorName, healthBonus, evasionRateBonus);
                    UserManager::GetInstance().equipPokemonArmor(
                            username, 0, pokemonId - 1, newArmor);
                }
                else
                {
                    std::cout << "无效宝可梦ID。" << std::endl;
                }
            }
            else if (choice == "5")
            {
                UI::GetInstance().displayAllPokemon(user->saveSlots[0]);
                std::cout << "请输入要卸下防具的宝可梦ID: ";
                int pokemonId;
                std::cin >> pokemonId;
                clearInputBuffer();
                if (pokemonId > 0 && pokemonId <= user->saveSlots[0].size())
                {
                    UserManager::GetInstance().unequipPokemonArmor(
                            username, 0, pokemonId - 1);
                }
                else
                {
                    std::cout << "无效宝可梦ID。" << std::endl;
                }
            }
            else if (choice == "6" || choice == "exit")
            {
                break;
            }
            else
            {
                std::cout << "无效选择，请重新输入。" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "用户 " << username << " 不存在或不是玩家。" << std::endl;
    }
}

void Game::playerMainMenu()
{
    std::string choice;
    while (true)
    {
        std::cout << "\n--- 主菜单 ---" << std::endl;
        std::cout << "输入 p 查看所有宝可梦" << std::endl;
        std::cout << "输入 f 进入战斗" << std::endl;
        std::cout << "输入 s 存档" << std::endl;
        std::cout << "输入 exit 退出" << std::endl;
        std::cout << "请输入你的选择: ";
        std::cin >> choice;
        clearInputBuffer();

        if (choice == "p" || choice == "P")
        {
            if (currentUser && !currentUser->saveSlots[0].empty())
            {
                UI::GetInstance().displayAllPokemon(currentUser->saveSlots[0]);
                std::cout << "当前出战宝可梦: "
                          << (playerActivePokemon ? playerActivePokemon->name
                                                  : "无") << std::endl;
                std::cout
                        << "输入宝可梦ID进行操作 (A1: 装备防具, A2: 卸下防具, D1: 装备饰品, D2: 卸下饰品, S: 选择出战宝可梦, exit: 返回主菜单): ";
                std::string pokemonChoice;
                std::getline(std::cin, pokemonChoice);

                if (pokemonChoice == "exit")
                {
                    continue;
                }
                else if (pokemonChoice == "S" || pokemonChoice == "s")
                {
                    selectActivePokemon(currentUser->saveSlots[0]);
                }
                else
                {
                    try
                    {
                        int pokemonId = std::stoi(pokemonChoice);
                        if (pokemonId > 0 &&
                            pokemonId <= currentUser->saveSlots[0].size())
                        {
                            std::shared_ptr<Pokemon> selectedPokemon = currentUser->saveSlots[0][
                                    pokemonId - 1];
                            std::cout << "已选择宝可梦: "
                                      << selectedPokemon->name << std::endl;
                            std::cout
                                    << "请选择操作 (A1: 装备防具, A2: 卸下防具, D1: 装备饰品, D2: 卸下饰品): ";
                            std::string equipChoice;
                            std::getline(std::cin, equipChoice);

                            if (equipChoice == "A1")
                            {
                                UserManager::GetInstance().equipPokemonArmor(
                                        currentUser->getUsername(), 0, pokemonId - 1,
                                        std::make_shared<Armor>("铁壁护甲", 20, 0.02));
                            }
                            else if (equipChoice == "A2")
                            {
                                UserManager::GetInstance().unequipPokemonArmor(
                                        currentUser->getUsername(), 0, pokemonId - 1);
                            }
                            else if (equipChoice == "D1")
                            {
                                UserManager::GetInstance().equipPokemonAccessory(
                                        currentUser->getUsername(), 0, pokemonId - 1,
                                        std::make_shared<Accessory>("力量手环", 5, 0, 0.05));
                            }
                            else if (equipChoice == "D2")
                            {
                                UserManager::GetInstance().unequipPokemonAccessory(
                                        currentUser->getUsername(), 0, pokemonId - 1);
                            }
                            else
                            {
                                std::cout << "无效操作。" << std::endl;
                            }
                        }
                        else
                        {
                            std::cout << "无效宝可梦ID。" << std::endl;
                        }
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cout << "无效输入。" << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "你还没有宝可梦。" << std::endl;
            }
        }
        else if (choice == "f" || choice == "F")
        {
            startBattle();
        }
        else if (choice == "s" || choice == "S")
        {
            saveLoadMenu();
        }
        else if (choice == "exit")
        {
            std::cout << "退出游戏。" << std::endl;
            exit(0);
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::saveLoadMenu()
{
    std::string choice;
    while (true)
    {
        std::cout << "\n--- 存档/载入菜单 ---" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            std::cout << (i + 1) << ". 存档槽位 " << (i + 1);
            if (!currentUser->saveSlots[i].empty())
            {
                std::cout << " (已保存)";
            }
            std::cout << std::endl;
        }
        std::cout << "sX 保存到槽位X (例如: s1)" << std::endl;
        std::cout << "lX 载入槽位X (例如: l1)" << std::endl;
        std::cout << "exit 返回主菜单" << std::endl;
        std::cout << "请输入你的选择: ";
        std::cin >> choice;
        clearInputBuffer();

        if (choice.length() == 2 && (choice[0] == 's' || choice[0] == 'S'))
        {
            int slotIndex = choice[1] - '1';
            if (slotIndex >= 0 && slotIndex < 3)
            {
                savePlayerSave(currentUser, slotIndex);
            }
            else
            {
                std::cout << "无效槽位。" << std::endl;
            }
        }
        else if (choice.length() == 2 && (choice[0] == 'l' || choice[0] == 'L'))
        {
            int slotIndex = choice[1] - '1';
            if (slotIndex >= 0 && slotIndex < 3)
            {
                loadPlayerSave(currentUser, slotIndex);
            }
            else
            {
                std::cout << "无效槽位。" << std::endl;
            }
        }
        else if (choice == "exit")
        {
            break;
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::chooseInitialPokemon(std::shared_ptr<User> player)
{
    std::string choice;
    while (true)
    {
        std::cout << "\n请选择你的初始宝可梦类型:" << std::endl;
        std::cout << "1. 火 (小火龙, 烈焰马, 暖暖猪, 火狐狸)" << std::endl;
        std::cout << "2. 草 (草苗龟, 樱花宝, 青藤蛇, 坐骑山羊)" << std::endl;
        std::cout << "3. 冰 (迷你冰, 雪童子, 冰伊布, 喷嚏熊)" << std::endl;
        std::cout << "请输入你的选择 (1-3): ";
        std::cin >> choice;
        clearInputBuffer();

        Pokemon::PokeType chosenType;
        if (choice == "1")
        {
            chosenType = Pokemon::FIRE;
        }
        else if (choice == "2")
        {
            chosenType = Pokemon::GRASS;
        }
        else if (choice == "3")
        {
            chosenType = Pokemon::ICE;
        }
        else
        {
            std::cout << "无效选择，请重新输入。" << std::endl;
            continue;
        }

        std::shared_ptr<Pokemon> initialPokemon = PokemonFactory::createPokemon(
                chosenType);
        player->saveSlots[0].push_back(initialPokemon);
        playerActivePokemon = initialPokemon;
        UserManager::GetInstance().saveUsers();
        std::cout << "恭喜你获得了初始宝可梦: " << initialPokemon->name << "！"
                  << std::endl;
        break;
    }
}

void Game::loadPlayerSave(std::shared_ptr<User> player, int slotIndex)
{
    if (player->saveSlots[slotIndex].empty())
    {
        std::cout << "存档槽位 " << (slotIndex + 1) << " 为空，无法载入。"
                  << std::endl;
        return;
    }
    currentUser->saveSlots[0] = player->saveSlots[slotIndex]; // Load all Pokemon from target save slot to current game slot
    std::cout << "已载入存档槽位 " << (slotIndex + 1) << "。" << std::endl;
    if (!currentUser->saveSlots[0].empty())
    {
        playerActivePokemon = currentUser->saveSlots[0][0];
        std::cout << "当前出战宝可梦设置为: " << playerActivePokemon->name
                  << "。" << std::endl;
    }
}

void Game::savePlayerSave(std::shared_ptr<User> player, int slotIndex)
{
    if (currentUser->saveSlots[0].empty())
    {
        std::cout << "当前没有宝可梦可供保存。" << std::endl;
        return;
    }
    player->saveSlots[slotIndex] = currentUser->saveSlots[0]; // Copy all Pokemon from current game slot to target save slot
    UserManager::GetInstance().saveUsers();
    std::cout << "已保存当前游戏到存档槽位 " << (slotIndex + 1) << "。"
              << std::endl;
}

void
Game::selectActivePokemon(std::vector<std::shared_ptr<Pokemon>> &pokemonList)
{
    if (pokemonList.empty())
    {
        std::cout << "你没有宝可梦可以选择。" << std::endl;
        playerActivePokemon = nullptr;
        return;
    }

    UI::GetInstance().displayAllPokemon(pokemonList);
    int choice;
    while (true)
    {
        std::cout << "请输入要选择的宝可梦ID: ";
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > pokemonList.size())
        {
            std::cout << "无效ID，请重新输入。" << std::endl;
            std::cin.clear();
            clearInputBuffer();
        }
        else
        {
            clearInputBuffer();
            playerActivePokemon = pokemonList[choice - 1];
            std::cout << "已选择 " << playerActivePokemon->name << " 作为出战宝可梦。"
                      << std::endl;
            break;
        }
    }
}

void Game::startBattle()
{
    if (!playerActivePokemon)
    {
        std::cout << "请先选择一个出战宝可梦才能进入战斗！" << std::endl;
        return;
    }

    std::vector<std::pair<std::string, Pokemon::PokeType>> enemyStages = {
            {"天星队（草）",   Pokemon::GRASS},
            {"天星队（火）",   Pokemon::FIRE},
            {"天星队（冰）",   Pokemon::ICE},
            {"天星队（飞行）", Pokemon::FLYING},
            {"天星队（幽灵）", Pokemon::GHOST}
    };

    bool playerRanAway = false;
    for (size_t i = 0; i < enemyStages.size(); ++i)
    {
        std::cout << "\n--- 剧情 ---" << std::endl;
        std::cout << "你来到了 " << enemyStages[i].first << " 的领地。"
                  << std::endl;
        std::cout << "\n--- 战斗开始！---" << std::endl;

        enemyActivePokemon = PokemonFactory::createPokemon(
                enemyStages[i].second);
        std::cout << "敌方派出了 " << enemyActivePokemon->name << "！"
                  << std::endl;

        while (!playerActivePokemon->isFainted() &&
               !enemyActivePokemon->isFainted())
        {
            UI::GetInstance().displayBattleStatus();
            std::cout << "输入 J 进行普攻，输入 K 释放技能: ";
            std::string action;
            std::getline(std::cin, action);

            if (action == "J" || action == "j")
            {
                std::cout << playerActivePokemon->name << " 发动了普通攻击！"
                          << std::endl;
                battleTurn(playerActivePokemon, enemyActivePokemon);
            }
            else if (action == "K" || action == "k")
            {
                if (playerActivePokemon->currentMagic >= 10)
                {
                    playerActivePokemon->useSkill(enemyActivePokemon);
                }
                else
                {
                    std::cout << playerActivePokemon->name << " 魔法值不足，无法释放技能！"
                              << std::endl;
                    continue; // Skip enemy turn if skill failed
                }
            }
            else if (action == "exit")
            {
                std::cout << "你逃跑了！" << std::endl;
                playerRanAway = true;
                break;
            }
            else
            {
                std::cout << "无效操作，请重新输入。" << std::endl;
                continue;
            }

            if (enemyActivePokemon->isFainted())
            {
                battleOutcome(true);
                enemyActivePokemon = nullptr;
                break;
            }

            // Enemy turn
            std::cout << enemyActivePokemon->name << " 发动了攻击！"
                      << std::endl;
            if (enemyActivePokemon->hasStatusEffect("Frozen"))
            {
                std::cout << enemyActivePokemon->name << " 被冻结了，无法行动！"
                          << std::endl;
            }
            else
            {
                battleTurn(enemyActivePokemon, playerActivePokemon);
            }

            if (playerActivePokemon->isFainted())
            {
                battleOutcome(false);
                enemyActivePokemon = nullptr;
                playerRanAway = true; // Player fainted, effectively ran away from this stage
                break;
            }
            // Regenerate magic for both Pokemon at the end of turn
            playerActivePokemon->restoreMagic(playerActivePokemon->magicRegen);
            enemyActivePokemon->restoreMagic(enemyActivePokemon->magicRegen);
            playerActivePokemon->decrementStatusEffects();
            enemyActivePokemon->decrementStatusEffects();
        }
        if (playerRanAway || playerActivePokemon->isFainted())
        {
            break;
        }
    }

    if (!playerRanAway && !playerActivePokemon->isFainted())
    {
        // Boss Battle
        std::cout << "\n--- 剧情 ---" << std::endl;
        std::cout << "你来到了天星队的老巢，仙后正在等着你！" << std::endl;
        std::cout << "\n--- Boss 战开始！---" << std::endl;
        enemyActivePokemon = PokemonFactory::createPokemon(Pokemon::GHOST);
        enemyActivePokemon->name = "仙后";
        enemyActivePokemon->level = 10; // Make boss stronger
        enemyActivePokemon->maxHealth *= 2;
        enemyActivePokemon->currentHealth = enemyActivePokemon->maxHealth;
        enemyActivePokemon->baseAttack *= 1.5;
        std::cout << "敌方派出了 " << enemyActivePokemon->name << "！"
                  << std::endl;

        while (!playerActivePokemon->isFainted() &&
               !enemyActivePokemon->isFainted())
        {
            UI::GetInstance().displayBattleStatus();
            std::cout << "输入 J 进行普攻，输入 K 释放技能: ";
            std::string action;
            std::getline(std::cin, action);

            if (action == "J" || action == "j")
            {
                std::cout << playerActivePokemon->name << " 发动了普通攻击！"
                          << std::endl;
                battleTurn(playerActivePokemon, enemyActivePokemon);
            }
            else if (action == "K" || action == "k")
            {
                if (playerActivePokemon->currentMagic >= 10)
                { // Example skill cost
                    playerActivePokemon->currentMagic -= 10;
                    std::cout << playerActivePokemon->name << " 释放了技能！"
                              << std::endl;
                    battleTurn(playerActivePokemon, enemyActivePokemon, true);
                }
                else
                {
                    std::cout << playerActivePokemon->name << " 魔法值不足，无法释放技能！"
                              << std::endl;
                    continue;
                }
            }
            else if (action == "exit")
            {
                std::cout << "你逃跑了！" << std::endl;
                playerRanAway = true;
                break;
            }
            else
            {
                std::cout << "无效操作，请重新输入。" << std::endl;
                continue;
            }

            if (enemyActivePokemon->isFainted())
            {
                battleOutcome(true);
                enemyActivePokemon = nullptr;
                break;
            }

            // Enemy turn
            std::cout << enemyActivePokemon->name << " 发动了攻击！"
                      << std::endl;
            if (enemyActivePokemon->hasStatusEffect("Frozen"))
            {
                std::cout << enemyActivePokemon->name << " 被冻结了，无法行动！"
                          << std::endl;
            }
            else
            {
                battleTurn(enemyActivePokemon, playerActivePokemon);
            }

            if (playerActivePokemon->isFainted())
            {
                battleOutcome(false);
                enemyActivePokemon = nullptr;
                return;
            }
            playerActivePokemon->restoreMagic(playerActivePokemon->magicRegen);
            enemyActivePokemon->restoreMagic(enemyActivePokemon->magicRegen);
            playerActivePokemon->decrementStatusEffects();
            enemyActivePokemon->decrementStatusEffects();
        }
    }
    if (enemyActivePokemon)
    { // If battle ended due to player running away
        enemyActivePokemon = nullptr;
    }
}

void Game::battleTurn(std::shared_ptr<Pokemon> attacker,
                      std::shared_ptr<Pokemon> defender, bool isSkill)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Check for evasion
    if (checkEvasion(defender))
    {
        std::cout << defender->name << " 成功闪避了 " << attacker->name
                  << " 的攻击！" << std::endl;
        return;
    }

    int damage = calculateDamage(attacker, defender, isSkill);

    // Check for critical hit
    if (checkCritical(attacker))
    {
        damage = static_cast<int>(damage * 1.5);
        std::cout << attacker->name << " 对 " << defender->name << " 造成了 "
                  << damage << " 点伤害！(暴击！)" << std::endl;
    }
    else
    {
        std::cout << attacker->name << " 对 " << defender->name << " 造成了 "
                  << damage << " 点伤害！" << std::endl;
    }

    defender->takeDamage(damage);
    std::cout << defender->name << " 剩余血量: " << defender->currentHealth
              << "/" << defender->maxHealth << std::endl;
}

int Game::calculateDamage(std::shared_ptr<Pokemon> attacker,
                          std::shared_ptr<Pokemon> defender, bool isSkill)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int damage = 0;

    if (isSkill)
    {
        // Example skill: deals 1.5x base attack damage
        damage = static_cast<int>(attacker->baseAttack * 1.5);
        std::cout << attacker->name << " 使用了强力攻击！" << std::endl;
    }
    else
    {
        // Normal attack: random damage around base attack
        std::uniform_int_distribution<> distrib(attacker->baseAttack - 2,
                                                attacker->baseAttack + 2);
        damage = distrib(gen);
        if (damage < 0) damage = 0;
    }

    // Simple damage reduction based on defender's defense
    damage -= defender->defense;
    if (damage < 0) damage = 0;
    return damage;
}

bool Game::checkEvasion(std::shared_ptr<Pokemon> defender)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    return distrib(gen) < defender->evasionRate;
}

bool Game::checkCritical(std::shared_ptr<Pokemon> attacker)
{
    std::shared_ptr<FirePokemon> fireAttacker = std::dynamic_pointer_cast<FirePokemon>(
            attacker);
    if (fireAttacker && fireAttacker->criticalTurns > 0)
    {
        fireAttacker->criticalTurns--;
        return true;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    return distrib(gen) < attacker->criticalRate;
}

void Game::battleOutcome(bool playerWon)
{
    if (playerWon)
    {
        std::cout << "\n恭喜你，战斗胜利！" << std::endl;
        playerActivePokemon->gainExperience(50); // Example experience gain
        // Add defeated enemy Pokemon to player's save slot
        if (enemyActivePokemon)
        {
            currentUser->saveSlots[0].push_back(
                    enemyActivePokemon);
            std::cout << "你获得了 " << enemyActivePokemon->name << "！"
                      << std::endl;
        }
    }
    else
    {
        std::cout << "\n很遗憾，你战败了。" << std::endl;
        std::cout << "游戏结束。" << std::endl;
        exit(0); // Exit the game on defeat
    }
    playerActivePokemon->currentHealth = playerActivePokemon->maxHealth; // Heal player's Pokemon after battle for simplicity
    playerActivePokemon->currentMagic = playerActivePokemon->maxMagic;
}


