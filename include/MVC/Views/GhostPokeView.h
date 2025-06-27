#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../Models/GhostPokeModel.h"

class GhostPokeView : public BasePokeView<GhostPokeModel>
{
public:
    explicit GhostPokeView(std::shared_ptr<GhostPokeModel> model) : BasePokeView(std::move(model))
    {
    }
};

