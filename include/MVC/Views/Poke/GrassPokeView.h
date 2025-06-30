#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../../Models/Poke/GrassPokeModel.h"

class GrassPokeView : public BasePokeView
{
public:
    explicit GrassPokeView(std::shared_ptr<GrassPokeModel> model) : BasePokeView(std::move(model))
    {
    }
};

