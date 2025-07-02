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
#include "../../include/Singletons/EquipManager.h"

void UI::displayAllPokemon(
        const std::vector<std::shared_ptr<Pokemon>> &pokemonList) const
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
        pokemonList[i]->displayStats();
    }
}

void UI::displayBattleStatus() const
{
    std::cout << "\n--- 战斗状态 ---" << std::endl;
    std::cout << "你的宝可梦: " << Game::GetInstance().playerActivePokemon->name
              << " (HP: "
              << Game::GetInstance().playerActivePokemon->currentHealth << "/"
              << Game::GetInstance().playerActivePokemon->maxHealth << ", MP: "
              << Game::GetInstance().playerActivePokemon->currentMagic << "/"
              << Game::GetInstance().playerActivePokemon->maxMagic << ")"
              << std::endl;
    std::cout << "敌方宝可梦: " << Game::GetInstance().enemyActivePokemon->name
              << " (HP: "
              << Game::GetInstance().enemyActivePokemon->currentHealth << "/"
              << Game::GetInstance().enemyActivePokemon->maxHealth << ")"
              << std::endl;
    std::cout << "--------------------" << std::endl;
}

