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
#include "../../include/Common/Types.h"

// Helper function to clear input buffer
void Game::clearInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Game::Game() : currentUser(nullptr), playerActivePokemon(nullptr),
               enemyActivePokemon(nullptr)
{
    // Constructor, userManager is already initialized
}

void Game::run()
{
    UI::GetInstance().showLoginScreen();
}

void Game::createNewPlayerSave(std::shared_ptr<User> player)
{
    // This function is called when a new player starts, and their first Pokemon is added to saveSlots[0]
    // No explicit action needed here beyond what's done in showLoginScreen for new players.
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
        playerActivePokemon = std::make_shared<Pokemon>(
                currentUser->saveSlots[0][0]);
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

void Game::equipPokemon(EquipType eType, Pokemon &pokemon)
{
    switch (eType)
    {
        case EquipType::Accessory:
        {
            // For simplicity, create a new Armor. In a real game, this would come from inventory.
            std::shared_ptr<Armor> newArmor = std::make_shared<Armor>(
                    "铁壁护甲",
                    20, 0.02);
            if (pokemon.armor)
            {
                std::cout << pokemon.name << " 已经装备了 "
                          << pokemon.armor->name
                          << "。是否替换？(y/n): ";
                std::string confirm;
                std::getline(std::cin, confirm);
                if (confirm == "y")
                {
                    pokemon.armor->removeEffect(pokemon);
                    pokemon.armor = nullptr;
                }
            }
            pokemon.armor = newArmor;
            pokemon.armor->applyEffect(pokemon);
            std::cout << pokemon.name << " 装备了 " << pokemon.armor->name
                      << "。"
                      << std::endl;
            break;
        }
        case EquipType::Armor:
        {
            // For simplicity, create a new Accessory. In a real game, this would come from inventory.
            std::shared_ptr<Accessory> newAccessory = std::make_shared<Accessory>(
                    "力量手环", 5, 0, 0.05);
            if (pokemon.accessory)
            {
                std::cout << pokemon.name << " 已经装备了 "
                          << pokemon.accessory->name << "。是否替换？(y/n): ";
                std::string confirm;
                std::getline(std::cin, confirm);
                if (confirm == "y")
                {
                    pokemon.accessory->removeEffect(pokemon);
                    pokemon.accessory = nullptr;
                }
            }
            pokemon.accessory = newAccessory;
            pokemon.accessory->applyEffect(pokemon);
            std::cout << pokemon.name << " 装备了 " << pokemon.accessory->name
                      << "。" << std::endl;
            break;
        }
    }
}

void Game::unequipPokemon(EquipType eType, Pokemon& pokemon)
{
    switch (eType)
    {
        case EquipType::Accessory:
            if (pokemon.armor)
            {
                pokemon.armor->removeEffect(pokemon);
                std::cout << pokemon.name << " 卸下了 " << pokemon.armor->name
                          << "。" << std::endl;
                pokemon.armor = nullptr;
            }
            else
            {
                std::cout << pokemon.name << " 没有装备防具。" << std::endl;
            }
            break;
        case EquipType::Armor:
            if (pokemon.accessory)
            {
                pokemon.accessory->removeEffect(pokemon);
                std::cout << pokemon.name << " 卸下了 "
                          << pokemon.accessory->name
                          << "。" << std::endl;
                pokemon.accessory = nullptr;
            }
            else
            {
                std::cout << pokemon.name << " 没有装备饰品。" << std::endl;
            }
            break;
    }
}

void Game::selectActivePokemon(std::vector<Pokemon> &pokemonList)
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
            playerActivePokemon = std::make_shared<Pokemon>(
                    pokemonList[choice - 1]);
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

    std::vector<std::pair<std::string, Pokemon::Type>> enemyStages = {
            {"天星队（草）",   Pokemon::GRASS},
            {"天星队（火）",   Pokemon::FIRE},
            {"天星队（冰）",   Pokemon::ICE},
            {"天星队（飞行）", Pokemon::FLYING},
            {"天星队（幽灵）", Pokemon::GHOST}
    };

    for (size_t i = 0; i < enemyStages.size(); ++i)
    {
        std::cout << "\n--- 剧情 ---" << std::endl;
        std::cout << "你来到了 " << enemyStages[i].first << " 的领地。"
                  << std::endl;
        std::cout << "\n--- 战斗开始！---" << std::endl;

        enemyActivePokemon = std::make_shared<Pokemon>(enemyStages[i].second);
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
                    continue; // Skip enemy turn if skill failed
                }
            }
            else if (action == "exit")
            {
                std::cout << "你逃跑了！" << std::endl;
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
            battleTurn(enemyActivePokemon, playerActivePokemon);

            if (playerActivePokemon->isFainted())
            {
                battleOutcome(false);
                enemyActivePokemon = nullptr;
                return; // Game over or return to main menu
            }
            // Regenerate magic for both Pokemon at the end of turn
            playerActivePokemon->restoreMagic(playerActivePokemon->magicRegen);
            enemyActivePokemon->restoreMagic(enemyActivePokemon->magicRegen);
        }
        if (playerActivePokemon->isFainted() || enemyActivePokemon)
        { // If enemyActivePokemon is not null, it means player ran away or battle ended prematurely
            break;
        }
    }

    if (!playerActivePokemon->isFainted())
    {
        // Boss Battle
        std::cout << "\n--- 剧情 ---" << std::endl;
        std::cout << "你来到了天星队的老巢，仙后正在等着你！" << std::endl;
        std::cout << "\n--- Boss 战开始！---" << std::endl;
        enemyActivePokemon = std::make_shared<Pokemon>(
                Pokemon::GHOST); // Example Boss type
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
            battleTurn(enemyActivePokemon, playerActivePokemon);

            if (playerActivePokemon->isFainted())
            {
                battleOutcome(false);
                enemyActivePokemon = nullptr;
                return;
            }
            playerActivePokemon->restoreMagic(playerActivePokemon->magicRegen);
            enemyActivePokemon->restoreMagic(enemyActivePokemon->magicRegen);
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
            currentUser->saveSlots[0].push_back(*enemyActivePokemon);
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
