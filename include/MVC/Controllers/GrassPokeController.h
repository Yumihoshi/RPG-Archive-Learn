#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../Models/GrassPokeModel.h"
#include "../Views/GrassPokeView.h"

class GrassPokeController : public BasePokeController
{
public:
    explicit GrassPokeController(std::shared_ptr<GrassPokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

