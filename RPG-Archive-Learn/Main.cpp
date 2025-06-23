#include <iostream>
#include "Singleton.h"
#include "FirePokeModel.h"
#include "FirePokeView.h"
#include "LogManager.h"

using namespace std;

int main()
{
    shared_ptr<FirePokeModel> f = make_shared<FirePokeModel>("小火龙", 200, 50, 10, CampType::Friend, 100, 20, 0.5, 0.5);
    FirePokeView fView(f);
    fView.ShowPokemonInfo();
    f->TakeDamage(100);
    fView.ShowPokemonInfo();
    f->TakeDamage(100);
    f->TakeDamage(100);
    return 0;
}
