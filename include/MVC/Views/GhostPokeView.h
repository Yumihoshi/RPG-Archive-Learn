#pragma once

#include "BasePokeView.h"
#include "../Models/GhostPokeModel.h"

class GhostPokeView : public BasePokeView<GhostPokeModel>
{
public:
    GhostPokeView(std::shared_ptr<GhostPokeModel> model) : BasePokeView(model)
    {
    }
};

