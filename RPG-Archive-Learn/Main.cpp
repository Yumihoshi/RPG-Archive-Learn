#include <iostream>
#include "Singleton.h"
#include "FirePokeModel.h"
#include "FirePokeView.h"
#include "LogManager.h"


int main()
{
    std::shared_ptr<FirePokeModel> f = std::make_shared<FirePokeModel>("小火龙", 200, 50, 10, CampType::Friend, 100, 20, 0.5, 0.5);
    FirePokeView fView(f);
    fView.ShowPokemonInfo();
    f->TakeDamage(100);
    for (size_t i = 0; i < 20; i++)
    {
        f->TakeDamage(5);
    }
    fView.ShowPokemonSkillInfo();
    return 0;
}
