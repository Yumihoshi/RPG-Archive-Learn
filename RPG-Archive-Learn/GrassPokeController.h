#pragma once

#include "BasePokeController.h"
#include "GrassPokeModel.h"
#include "GrassPokeView.h"

class GrassPokeController : public BasePokeController<GrassPokeModel, GrassPokeView>
{
public:
    GrassPokeController(std::shared_ptr<GrassPokeModel> model) : BasePokeController(model)
    {
    }
};

