#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../../Models/Poke/FirePokeModel.h"


class FirePokeView : public BasePokeView
{
public:
    explicit FirePokeView(std::shared_ptr<FirePokeModel> model) : BasePokeView(std::move(model))
    {
    }

private:
};

