#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../../Models/Poke/GrassPokeModel.h"
#include "../../Views/Poke/GrassPokeView.h"

class GrassPokeController : public BasePokeController
{
public:
    explicit GrassPokeController(std::shared_ptr<GrassPokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

