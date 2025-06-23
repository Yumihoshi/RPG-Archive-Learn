#include "PokemonView.h"
#include "LogManager.h"

using namespace std;

void PokemonView::ShowPokemonInfo()
{
    LogManager::GetInstance().PrintByChar("\n======");
    LogManager::GetInstance().PrintByChar("宝可梦信息面板", LogColor::Yellow);
    LogManager::GetInstance().PrintByChar("======\n");
}

void PokemonView::ShowPokemonSkillInfo()
{
    LogManager::GetInstance().PrintByChar("\n======");
    LogManager::GetInstance().PrintByChar("宝可梦技能信息面板", LogColor::Yellow);
    LogManager::GetInstance().PrintByChar("======\n");
}
