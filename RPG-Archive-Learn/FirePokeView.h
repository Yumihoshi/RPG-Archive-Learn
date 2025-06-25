#pragma once

#include "PokemonView.h"
#include "FirePokeModel.h"


class FirePokeView : public PokemonView
{
public:
    std::shared_ptr<FirePokeModel> ModelPtr;

    FirePokeView(std::shared_ptr<FirePokeModel> model);
    void ShowPokemonInfo() override;
    void ShowPokemonSkillInfo() override;
private:
};

