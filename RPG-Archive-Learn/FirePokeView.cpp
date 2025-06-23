#include <string>
#include "FirePokeView.h"
#include "LogManager.h"

using namespace std;

FirePokeView::FirePokeView(shared_ptr<FirePokeModel> model)
{
    ModelPtr = model;
}

void FirePokeView::ShowPokemonInfo()
{
    LogManager::GetInstance().PrintByChar("\n======");
    LogManager::GetInstance().PrintByChar("宝可梦信息面板", LogColor::Yellow);
    LogManager::GetInstance().PrintByChar("======\n");
    LogManager::GetInstance().PrintByChar("名称：" + (*ModelPtr).GetName() + "\n");
    LogManager::GetInstance().PrintByChar("血量：", LogColor::Red);
    LogManager::GetInstance().PrintByChar(to_string((*ModelPtr).GetCurHp()) +
        "/" + to_string((*ModelPtr).GetMaxHp()) + "\n");
    LogManager::GetInstance().PrintByChar("魔法值：", LogColor::Blue);
    LogManager::GetInstance().PrintByChar(to_string((*ModelPtr).GetCurMp()) + "/" +
        to_string((*ModelPtr).GetMaxMp()) + "\n\n");
}

void FirePokeView::ShowPokemonSkillInfo()
{

}
