#include "Game.h"
#include "Pokemon.h"
#include "Equipment.h"
#include <iostream>
#include <limits>
#include <random>
#include <algorithm>

// Helper function to clear input buffer
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Game::Game() : currentUser(nullptr), playerActivePokemon(nullptr), enemyActivePokemon(nullptr) {
    // Constructor, userManager is already initialized
}

void Game::run() {
    showLoginScreen();
}

void Game::showLoginScreen() {
    std::string username, password;
    int choice;

    while (true) {
        std::cout << "\n--- 登录/注册 ---" << std::endl;
        std::cout << "1. 登录" << std::endl;
        std::cout << "2. 注册" << std::endl;
        std::cout << "3. 退出游戏" << std::endl;
        std::cout << "请输入您的选择: \n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "无效输入，请重新输入数字。" << std::endl;
            std::cin.clear();
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 1) {
            std::cout << "请输入用户名: \n";
            std::getline(std::cin, username);
            std::cout << "请输入密码: \n";
            std::getline(std::cin, password);

            currentUser = userManager.login(username, password);
            if (currentUser) {
                std::cout << "登录成功！" << std::endl;
                if (currentUser->getUserType() == User::ADMIN) {
                    showAdminMenu();
                } else {
                    // Check if it's a new player (no saved games)
                    bool newPlayer = true;
                    for (const auto& slot : currentUser->saveSlots) {
                        if (!slot.empty()) {
                            newPlayer = false;
                            break;
                        }
                    }

                    if (newPlayer) {
                        std::cout << "欢迎新玩家！请选择你的初始宝可梦：" << std::endl;
                        std::cout << "1. 火属性 (小火龙)" << std::endl;
                        std::cout << "2. 草属性 (草苗龟)" << std::endl;
                        std::cout << "3. 冰属性 (迷你冰)" << std::endl;
                        int pokemonChoice;
                        while (true) {
                            std::cout << "请输入选择 (1-3): ";
                            std::cin >> pokemonChoice;
                            if (std::cin.fail() || pokemonChoice < 1 || pokemonChoice > 3) {
                                std::cout << "无效选择，请重新输入。" << std::cin.fail() << std::endl;
                                std::cin.clear();
                                clearInputBuffer();
                            } else {
                                clearInputBuffer();
                                break;
                            }
                        }

                        Pokemon::Type initialType;
                        switch (pokemonChoice) {
                            case 1: initialType = Pokemon::FIRE; break;
                            case 2: initialType = Pokemon::GRASS; break;
                            case 3: initialType = Pokemon::ICE; break;
                            default: initialType = Pokemon::FIRE; break; // Should not happen
                        }
                        currentUser->saveSlots[0].push_back(Pokemon(initialType));
                        std::cout << "你选择了 " << currentUser->saveSlots[0][0].name << " 作为你的初始宝可梦！" << std::endl;
                        playerActivePokemon = &currentUser->saveSlots[0][0]; // Set initial active Pokemon
                        showPlayerMainMenu();
                    } else {
                        showSaveLoadMenu();
                    }
                }
                break; // Exit login loop on successful login
            } else {
                std::cout << "用户名或密码错误，请重试。" << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "请输入新用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入新密码: ";
            std::getline(std::cin, password);
            userManager.registerUser(username, password, User::PLAYER);
        } else if (choice == 3) {
            std::cout << "感谢游玩，再见！" << std::endl;
            exit(0);
        } else {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::showAdminMenu() {
    std::string input;
    while (true) {
        std::cout << "\n--- 管理员菜单 ---" << std::endl;
        std::cout << "1. 创建用户" << std::endl;
        std::cout << "2. 删除用户" << std::endl;
        std::cout << "3. 更新用户密码" << std::endl;
        std::cout << "4. 列出所有用户" << std::endl;
        std::cout << "exit. 返回登录界面" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input == "1") {
            std::string username, password, typeStr;
            User::UserType type;
            std::cout << "请输入新用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入密码: ";
            std::getline(std::cin, password);
            while (true) {
                std::cout << "请输入用户类型 (player/admin): ";
                std::getline(std::cin, typeStr);
                if (typeStr == "player") { type = User::PLAYER; break; }
                else if (typeStr == "admin") { type = User::ADMIN; break; }
                else { std::cout << "无效类型，请重新输入。" << std::endl; }
            }
            userManager.createUser(username, password, type);
        } else if (input == "2") {
            std::string username;
            std::cout << "请输入要删除的用户名: ";
            std::getline(std::cin, username);
            userManager.deleteUser(username);
        } else if (input == "3") {
            std::string username, newPassword;
            std::cout << "请输入要更新密码的用户名: ";
            std::getline(std::cin, username);
            std::cout << "请输入新密码: ";
            std::getline(std::cin, newPassword);
            userManager.updateUserPassword(username, newPassword);
        } else if (input == "4") {
            userManager.listAllUsers();
        } else if (input == "exit") {
            currentUser = nullptr;
            showLoginScreen();
            break;
        } else {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::showPlayerMainMenu() {
    std::string input;
    while (true) {
        std::cout << "\n--- 主菜单 ---" << std::endl;
        std::cout << "输入 p 查看所有宝可梦" << std::endl;
        std::cout << "输入 f 进入战斗" << std::endl;
        std::cout << "输入 s 存档" << std::endl;
        std::cout << "输入 exit 退出到登录界面" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input == "p") {
            showPokemonManagementMenu();
        } else if (input == "f") {
            startBattle();
        } else if (input == "s") {
            showSaveLoadMenu();
        } else if (input == "exit") {
            currentUser = nullptr;
            showLoginScreen();
            break;
        } else {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::showSaveLoadMenu() {
    std::string input;
    while (true) {
        std::cout << "\n--- 存档菜单 ---" << std::endl;
        for (size_t i = 0; i < currentUser->saveSlots.size(); ++i) {
            std::cout << (i + 1) << ". 存档槽位 " << (i + 1) << (currentUser->saveSlots[i].empty() ? " (空)" : " (有数据)") << std::endl;
        }
        std::cout << "输入 load [槽位号] 载入存档" << std::endl;
        std::cout << "输入 save [槽位号] 保存存档" << std::endl;
        std::cout << "输入 exit 返回主菜单" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input.rfind("load ", 0) == 0) { // Check if input starts with "load "
            int slotIndex = std::stoi(input.substr(5)) - 1;
            if (slotIndex >= 0 && slotIndex < currentUser->saveSlots.size()) {
                loadPlayerSave(currentUser, slotIndex);
            } else {
                std::cout << "无效的槽位号。" << std::endl;
            }
        } else if (input.rfind("save ", 0) == 0) { // Check if input starts with "save "
            int slotIndex = std::stoi(input.substr(5)) - 1;
            if (slotIndex >= 0 && slotIndex < currentUser->saveSlots.size()) {
                savePlayerSave(currentUser, slotIndex);
            } else {
                std::cout << "无效的槽位号。" << std::endl;
            }
        } else if (input == "exit") {
            break;
        } else {
            std::cout << "无效选择，请重新输入。" << std::endl;
        }
    }
}

void Game::createNewPlayerSave(User* player) {
    // This function is called when a new player starts, and their first Pokemon is added to saveSlots[0]
    // No explicit action needed here beyond what's done in showLoginScreen for new players.
}

void Game::loadPlayerSave(User* player, int slotIndex) {
    if (player->saveSlots[slotIndex].empty()) {
        std::cout << "存档槽位 " << (slotIndex + 1) << " 为空，无法载入。" << std::endl;
        return;
    }
    currentUser->saveSlots[0] = player->saveSlots[slotIndex]; // Load all Pokemon from target save slot to current game slot
    std::cout << "已载入存档槽位 " << (slotIndex + 1) << "。" << std::endl;
    if (!currentUser->saveSlots[0].empty()) {
        playerActivePokemon = &currentUser->saveSlots[0][0];
        std::cout << "当前出战宝可梦设置为: " << playerActivePokemon->name << "。" << std::endl;
    }
}

void Game::savePlayerSave(User* player, int slotIndex) {
    if (currentUser->saveSlots[0].empty()) {
        std::cout << "当前没有宝可梦可供保存。" << std::endl;
        return;
    }
    player->saveSlots[slotIndex] = currentUser->saveSlots[0]; // Copy all Pokemon from current game slot to target save slot
    userManager.saveUsers();
    std::cout << "已保存当前游戏到存档槽位 " << (slotIndex + 1) << "。" << std::endl;
}

void Game::showPokemonManagementMenu() {
    std::string input;
    if (!playerActivePokemon) {
        std::cout << "请先选择一个出战宝可梦。" << std::endl;
        selectActivePokemon(currentUser->saveSlots[0]); // Assuming slot 0 is the current game
        if (!playerActivePokemon) return; // If still no active Pokemon, return
    }

    while (true) {
        std::cout << "\n--- 宝可梦管理 ---" << std::endl;
        displayAllPokemon(currentUser->saveSlots[0]); // Display Pokemon from the current save slot
        std::cout << "当前出战宝可梦: " << (playerActivePokemon ? playerActivePokemon->name : "无") << std::endl;
        std::cout << "输入 [宝可梦ID] 选择出战宝可梦" << std::endl;
        std::cout << "输入 A1 [宝可梦ID] 装备防具" << std::endl;
        std::cout << "输入 A2 [宝可梦ID] 卸下防具" << std::endl;
        std::cout << "输入 D1 [宝可梦ID] 装备饰品" << std::endl;
        std::cout << "输入 D2 [宝可梦ID] 卸下饰品" << std::endl;
        std::cout << "输入 exit 返回主菜单" << std::endl;
        std::cout << "请输入您的选择: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        } else if (input.rfind("A1 ", 0) == 0) {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < currentUser->saveSlots[0].size()) {
                equipPokemon(&currentUser->saveSlots[0][pokemonId]);
            } else {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        } else if (input.rfind("A2 ", 0) == 0) {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < currentUser->saveSlots[0].size()) {
                unequipPokemon(&currentUser->saveSlots[0][pokemonId]);
            } else {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        } else if (input.rfind("D1 ", 0) == 0) {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < currentUser->saveSlots[0].size()) {
                equipPokemon(&currentUser->saveSlots[0][pokemonId]); // Re-using equip for accessory
            } else {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        } else if (input.rfind("D2 ", 0) == 0) {
            int pokemonId = std::stoi(input.substr(3)) - 1;
            if (pokemonId >= 0 && pokemonId < currentUser->saveSlots[0].size()) {
                unequipPokemon(&currentUser->saveSlots[0][pokemonId]); // Re-using unequip for accessory
            } else {
                std::cout << "无效的宝可梦ID。" << std::endl;
            }
        } else {
            try {
                int pokemonId = std::stoi(input) - 1;
                if (pokemonId >= 0 && pokemonId < currentUser->saveSlots[0].size()) {
                    playerActivePokemon = &currentUser->saveSlots[0][pokemonId];
                    std::cout << "已选择 " << playerActivePokemon->name << " 作为出战宝可梦。" << std::endl;
                } else {
                    std::cout << "无效的宝可梦ID。" << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "无效选择，请重新输入。" << std::endl;
            }
        }
    }
}

void Game::displayAllPokemon(const std::vector<Pokemon>& pokemonList) const {
    if (pokemonList.empty()) {
        std::cout << "你还没有任何宝可梦。" << std::endl;
        return;
    }
    std::cout << "\n--- 你的宝可梦 ---" << std::endl;
    for (size_t i = 0; i < pokemonList.size(); ++i) {
        std::cout << "ID: " << (i + 1) << std::endl;
        pokemonList[i].displayStats();
    }
}

void Game::equipPokemon(Pokemon* pokemon) {
    std::string equipChoice;
    std::cout << "请选择要装备的类型 (A: 防具, D: 饰品): ";
    std::getline(std::cin, equipChoice);

    if (equipChoice == "A") {
        // For simplicity, create a new Armor. In a real game, this would come from inventory.
        Armor* newArmor = new Armor("铁壁护甲", 20, 0.02);
        if (pokemon->armor) {
            std::cout << pokemon->name << " 已经装备了 " << pokemon->armor->name << "。是否替换？(y/n): ";
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y") {
                pokemon->armor->removeEffect(pokemon);
                delete pokemon->armor;
                pokemon->armor = nullptr;
            } else {
                delete newArmor; // Clean up if not used
                return;
            }
        }
        pokemon->armor = newArmor;
        pokemon->armor->applyEffect(pokemon);
        std::cout << pokemon->name << " 装备了 " << pokemon->armor->name << "。" << std::endl;
    } else if (equipChoice == "D") {
        // For simplicity, create a new Accessory. In a real game, this would come from inventory.
        Accessory* newAccessory = new Accessory("力量手环", 5, 0, 0.05);
        if (pokemon->accessory) {
            std::cout << pokemon->name << " 已经装备了 " << pokemon->accessory->name << "。是否替换？(y/n): ";
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y") {
                pokemon->accessory->removeEffect(pokemon);
                delete pokemon->accessory;
                pokemon->accessory = nullptr;
            } else {
                delete newAccessory; // Clean up if not used
                return;
            }
        }
        pokemon->accessory = newAccessory;
        pokemon->accessory->applyEffect(pokemon);
        std::cout << pokemon->name << " 装备了 " << pokemon->accessory->name << "。" << std::endl;
    } else {
        std::cout << "无效的装备类型。" << std::endl;
    }
}

void Game::unequipPokemon(Pokemon* pokemon) {
    std::string unequipChoice;
    std::cout << "请选择要卸下的类型 (A: 防具, D: 饰品): ";
    std::getline(std::cin, unequipChoice);

    if (unequipChoice == "A") {
        if (pokemon->armor) {
            pokemon->armor->removeEffect(pokemon);
            std::cout << pokemon->name << " 卸下了 " << pokemon->armor->name << "。" << std::endl;
            delete pokemon->armor;
            pokemon->armor = nullptr;
        } else {
            std::cout << pokemon->name << " 没有装备防具。" << std::endl;
        }
    } else if (unequipChoice == "D") {
        if (pokemon->accessory) {
            pokemon->accessory->removeEffect(pokemon);
            std::cout << pokemon->name << " 卸下了 " << pokemon->accessory->name << "。" << std::endl;
            delete pokemon->accessory;
            pokemon->accessory = nullptr;
        } else {
            std::cout << pokemon->name << " 没有装备饰品。" << std::endl;
        }
    } else {
        std::cout << "无效的卸下类型。" << std::endl;
    }
}

void Game::selectActivePokemon(std::vector<Pokemon>& pokemonList) {
    if (pokemonList.empty()) {
        std::cout << "你没有宝可梦可以选择。" << std::endl;
        playerActivePokemon = nullptr;
        return;
    }

    displayAllPokemon(pokemonList);
    int choice;
    while (true) {
        std::cout << "请输入要选择的宝可梦ID: ";
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > pokemonList.size()) {
            std::cout << "无效ID，请重新输入。" << std::endl;
            std::cin.clear();
            clearInputBuffer();
        } else {
            clearInputBuffer();
            playerActivePokemon = &pokemonList[choice - 1];
            std::cout << "已选择 " << playerActivePokemon->name << " 作为出战宝可梦。" << std::endl;
            break;
        }
    }
}

void Game::startBattle() {
    if (!playerActivePokemon) {
        std::cout << "请先选择一个出战宝可梦才能进入战斗！" << std::endl;
        return;
    }

    std::vector<std::pair<std::string, Pokemon::Type>> enemyStages = {
        {"天星队（草）", Pokemon::GRASS},
        {"天星队（火）", Pokemon::FIRE},
        {"天星队（冰）", Pokemon::ICE},
        {"天星队（飞行）", Pokemon::FLYING},
        {"天星队（幽灵）", Pokemon::GHOST}
    };

    for (size_t i = 0; i < enemyStages.size(); ++i) {
        std::cout << "\n--- 剧情 ---" << std::endl;
        std::cout << "你来到了 " << enemyStages[i].first << " 的领地。" << std::endl;
        std::cout << "\n--- 战斗开始！---" << std::endl;

        enemyActivePokemon = new Pokemon(enemyStages[i].second);
        std::cout << "敌方派出了 " << enemyActivePokemon->name << "！" << std::endl;

        while (!playerActivePokemon->isFainted() && !enemyActivePokemon->isFainted()) {
            displayBattleStatus();
            std::cout << "输入 J 进行普攻，输入 K 释放技能: ";
            std::string action;
            std::getline(std::cin, action);

            if (action == "J" || action == "j") {
                std::cout << playerActivePokemon->name << " 发动了普通攻击！" << std::endl;
                battleTurn(playerActivePokemon, enemyActivePokemon);
            } else if (action == "K" || action == "k") {
                if (playerActivePokemon->currentMagic >= 10) { // Example skill cost
                    playerActivePokemon->currentMagic -= 10;
                    std::cout << playerActivePokemon->name << " 释放了技能！" << std::endl;
                    battleTurn(playerActivePokemon, enemyActivePokemon, true);
                } else {
                    std::cout << playerActivePokemon->name << " 魔法值不足，无法释放技能！" << std::endl;
                    continue; // Skip enemy turn if skill failed
                }
            } else if (action == "exit") {
                std::cout << "你逃跑了！" << std::endl;
                break;
            } else {
                std::cout << "无效操作，请重新输入。" << std::endl;
                continue;
            }

            if (enemyActivePokemon->isFainted()) {
                battleOutcome(true);
                delete enemyActivePokemon;
                enemyActivePokemon = nullptr;
                break;
            }

            // Enemy turn
            std::cout << enemyActivePokemon->name << " 发动了攻击！" << std::endl;
            battleTurn(enemyActivePokemon, playerActivePokemon);

            if (playerActivePokemon->isFainted()) {
                battleOutcome(false);
                delete enemyActivePokemon;
                enemyActivePokemon = nullptr;
                return; // Game over or return to main menu
            }
            // Regenerate magic for both Pokemon at the end of turn
            playerActivePokemon->restoreMagic(playerActivePokemon->magicRegen);
            enemyActivePokemon->restoreMagic(enemyActivePokemon->magicRegen);
        }
        if (playerActivePokemon->isFainted() || enemyActivePokemon) { // If enemyActivePokemon is not null, it means player ran away or battle ended prematurely
            break;
        }
    }

    if (!playerActivePokemon->isFainted()) {
        // Boss Battle
        std::cout << "\n--- 剧情 ---" << std::endl;
        std::cout << "你来到了天星队的老巢，仙后正在等着你！" << std::endl;
        std::cout << "\n--- Boss 战开始！---" << std::endl;
        enemyActivePokemon = new Pokemon(Pokemon::GHOST); // Example Boss type
        enemyActivePokemon->name = "仙后";
        enemyActivePokemon->level = 10; // Make boss stronger
        enemyActivePokemon->maxHealth *= 2;
        enemyActivePokemon->currentHealth = enemyActivePokemon->maxHealth;
        enemyActivePokemon->baseAttack *= 1.5;
        std::cout << "敌方派出了 " << enemyActivePokemon->name << "！" << std::endl;

        while (!playerActivePokemon->isFainted() && !enemyActivePokemon->isFainted()) {
            displayBattleStatus();
            std::cout << "输入 J 进行普攻，输入 K 释放技能: ";
            std::string action;
            std::getline(std::cin, action);

            if (action == "J" || action == "j") {
                std::cout << playerActivePokemon->name << " 发动了普通攻击！" << std::endl;
                battleTurn(playerActivePokemon, enemyActivePokemon);
            } else if (action == "K" || action == "k") {
                if (playerActivePokemon->currentMagic >= 10) { // Example skill cost
                    playerActivePokemon->currentMagic -= 10;
                    std::cout << playerActivePokemon->name << " 释放了技能！" << std::endl;
                    battleTurn(playerActivePokemon, enemyActivePokemon, true);
                } else {
                    std::cout << playerActivePokemon->name << " 魔法值不足，无法释放技能！" << std::endl;
                    continue;
                }
            } else if (action == "exit") {
                std::cout << "你逃跑了！" << std::endl;
                break;
            } else {
                std::cout << "无效操作，请重新输入。" << std::endl;
                continue;
            }

            if (enemyActivePokemon->isFainted()) {
                battleOutcome(true);
                delete enemyActivePokemon;
                enemyActivePokemon = nullptr;
                break;
            }

            // Enemy turn
            std::cout << enemyActivePokemon->name << " 发动了攻击！" << std::endl;
            battleTurn(enemyActivePokemon, playerActivePokemon);

            if (playerActivePokemon->isFainted()) {
                battleOutcome(false);
                delete enemyActivePokemon;
                enemyActivePokemon = nullptr;
                return;
            }
            playerActivePokemon->restoreMagic(playerActivePokemon->magicRegen);
            enemyActivePokemon->restoreMagic(enemyActivePokemon->magicRegen);
        }
    }
    if (enemyActivePokemon) { // If battle ended due to player running away
        delete enemyActivePokemon;
        enemyActivePokemon = nullptr;
    }
}

void Game::battleTurn(Pokemon* attacker, Pokemon* defender, bool isSkill) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Check for evasion
    if (checkEvasion(defender)) {
        std::cout << defender->name << " 成功闪避了 " << attacker->name << " 的攻击！" << std::endl;
        return;
    }

    int damage = calculateDamage(attacker, defender, isSkill);

    // Check for critical hit
    if (checkCritical(attacker)) {
        damage = static_cast<int>(damage * 1.5);
        std::cout << attacker->name << " 对 " << defender->name << " 造成了 " << damage << " 点伤害！(暴击！)" << std::endl;
    } else {
        std::cout << attacker->name << " 对 " << defender->name << " 造成了 " << damage << " 点伤害！" << std::endl;
    }

    defender->takeDamage(damage);
    std::cout << defender->name << " 剩余血量: " << defender->currentHealth << "/" << defender->maxHealth << std::endl;
}

int Game::calculateDamage(Pokemon* attacker, Pokemon* defender, bool isSkill) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int damage = 0;

    if (isSkill) {
        // Example skill: deals 1.5x base attack damage
        damage = static_cast<int>(attacker->baseAttack * 1.5);
        std::cout << attacker->name << " 使用了强力攻击！" << std::endl;
    } else {
        // Normal attack: random damage around base attack
        std::uniform_int_distribution<> distrib(attacker->baseAttack - 2, attacker->baseAttack + 2);
        damage = distrib(gen);
        if (damage < 0) damage = 0;
    }

    // Simple damage reduction based on defender's defense
    damage -= defender->defense;
    if (damage < 0) damage = 0;
    return damage;
}

bool Game::checkEvasion(Pokemon* defender) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    return distrib(gen) < defender->evasionRate;
}

bool Game::checkCritical(Pokemon* attacker) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    return distrib(gen) < attacker->criticalRate;
}

void Game::displayBattleStatus() const {
    std::cout << "\n--- 战斗状态 ---" << std::endl;
    std::cout << "你的宝可梦: " << playerActivePokemon->name << " (HP: " << playerActivePokemon->currentHealth << "/" << playerActivePokemon->maxHealth << ", MP: " << playerActivePokemon->currentMagic << "/" << playerActivePokemon->maxMagic << ")" << std::endl;
    std::cout << "敌方宝可梦: " << enemyActivePokemon->name << " (HP: " << enemyActivePokemon->currentHealth << "/" << enemyActivePokemon->maxHealth << ")" << std::endl;
    std::cout << "--------------------" << std::endl;
}

void Game::battleOutcome(bool playerWon) {
    if (playerWon) {
        std::cout << "\n恭喜你，战斗胜利！" << std::endl;
        playerActivePokemon->gainExperience(50); // Example experience gain
        // Add defeated enemy Pokemon to player's save slot
        if (enemyActivePokemon) {
            currentUser->saveSlots[0].push_back(*enemyActivePokemon);
            std::cout << "你获得了 " << enemyActivePokemon->name << "！" << std::endl;
        }
    } else {
        std::cout << "\n很遗憾，你战败了。" << std::endl;
        std::cout << "游戏结束。" << std::endl;
        exit(0); // Exit the game on defeat
    }
    playerActivePokemon->currentHealth = playerActivePokemon->maxHealth; // Heal player's Pokemon after battle for simplicity
    playerActivePokemon->currentMagic = playerActivePokemon->maxMagic;
}
