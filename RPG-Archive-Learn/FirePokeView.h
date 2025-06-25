#pragma once

#include "BasePokeView.h"
#include "FirePokeModel.h"


class FirePokeView : public BasePokeView
{
public:
    std::shared_ptr<FirePokeModel> ModelPtr;

    FirePokeView(std::shared_ptr<FirePokeModel> model);
    void ShowPokemonInfo() override;
    void ShowPokemonSkillInfo() override;
private:
};

