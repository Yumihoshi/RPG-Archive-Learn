#include <iostream>
#include <Windows.h>
#include "Singleton.h"
#include "FirePokeModel.h"
#include "FirePokeView.h"
#include "LogManager.h"
#include "Decoration.h"
#include "Armor.h"


int main()
{
    SetConsoleOutputCP(65001);
    std::shared_ptr<FirePokeModel> f = std::make_shared<FirePokeModel>("小火龙", CampType::Friend);
    FirePokeView fView(f);
    fView.ShowPokemonInfo();
    f->TakeDamage(100);
    for (size_t i = 0; i < 20; i++)
    {
        f->TakeDamage(5);
    }
    fView.ShowPokemonSkillInfo();
    std::shared_ptr<Decoration> w = std::make_shared<Decoration>("项链", 10, 20, 0.5);
    std::shared_ptr<Armor> a = std::make_shared<Armor>("锁链甲", 100, 0.5);
    f->Equip(w);
    f->Equip(a);
    fView.ShowPokemonInfo();
    return 0;
}
