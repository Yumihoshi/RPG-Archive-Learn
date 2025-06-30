#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../../Models/Poke/GhostPokeModel.h"

class GhostPokeView : public BasePokeView
{
public:
    explicit GhostPokeView(std::shared_ptr<GhostPokeModel> model) : BasePokeView(std::move(model))
    {
    }
};

