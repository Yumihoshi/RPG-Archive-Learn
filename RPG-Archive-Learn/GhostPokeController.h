#pragma once

#include "BasePokeController.h"
#include "GhostPokeModel.h"
#include "GhostPokeView.h"

class GhostPokeController : public BasePokeController<GhostPokeModel, GhostPokeView>
{
public:
    GhostPokeController(std::shared_ptr<GhostPokeModel> model) : BasePokeController(model)
    {
    }
};

