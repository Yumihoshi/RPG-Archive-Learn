#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../Models/GhostPokeModel.h"
#include "../Views/GhostPokeView.h"

class GhostPokeController : public BasePokeController
{
public:
    explicit GhostPokeController(std::shared_ptr<GhostPokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

