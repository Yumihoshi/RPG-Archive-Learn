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
    LogManager::GetInstance().PrintByChar("===信息面板===\n");
    LogManager::GetInstance().PrintByChar("名称：" + (*ModelPtr).GetName() + "\n");
    LogManager::GetInstance().PrintByChar("血量：" + to_string((*ModelPtr).GetCurHp()) + "\n");
}

void FirePokeView::ShowPokemonSkillInfo()
{

}
