#pragma once
#include "PokemonView.h"
#include "FirePokeModel.h"
using namespace std;

class FirePokeView : public PokemonView
{
public:
    shared_ptr<FirePokeModel> ModelPtr;

    FirePokeView(shared_ptr<FirePokeModel> model);
    void ShowPokemonInfo() override;
    void ShowPokemonSkillInfo() override;
private:
};

