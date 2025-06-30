#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../../Models/Poke/GhostPokeModel.h"
#include "../../Views/Poke/GhostPokeView.h"

class GhostPokeController : public BasePokeController
{
public:
    explicit GhostPokeController(std::shared_ptr<GhostPokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

