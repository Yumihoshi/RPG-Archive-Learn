#pragma once

#include "BasePokeController.h"
#include "../Models/GhostPokeModel.h"
#include "../Views/GhostPokeView.h"

class GhostPokeController : public BasePokeController<GhostPokeModel, GhostPokeView>
{
public:
    GhostPokeController(std::shared_ptr<GhostPokeModel> model) : BasePokeController(model)
    {
    }
};

