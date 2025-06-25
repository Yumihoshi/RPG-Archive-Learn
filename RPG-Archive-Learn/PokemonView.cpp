#include "BasePokeView.h"
#include "LogManager.h"


void BasePokeView::ShowPokemonInfo()
{
    LogManager::GetInstance().PrintByChar("\n======");
    LogManager::GetInstance().PrintByChar("宝可梦信息面板", LogColor::Yellow);
    LogManager::GetInstance().PrintByChar("======\n");
}

void BasePokeView::ShowPokemonSkillInfo()
{
    LogManager::GetInstance().PrintByChar("\n======");
    LogManager::GetInstance().PrintByChar("宝可梦技能信息面板", LogColor::Yellow);
    LogManager::GetInstance().PrintByChar("======\n");
}
