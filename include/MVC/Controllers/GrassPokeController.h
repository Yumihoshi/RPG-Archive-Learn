#pragma once

#include "BasePokeController.h"
#include "../Models/GrassPokeModel.h"
#include "../Views/GrassPokeView.h"

class GrassPokeController : public BasePokeController<GrassPokeModel, GrassPokeView>
{
public:
    GrassPokeController(std::shared_ptr<GrassPokeModel> model) : BasePokeController(model)
    {
    }
};

