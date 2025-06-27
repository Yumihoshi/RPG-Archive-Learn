#pragma once

#include "BasePokeController.h"
#include "../Models/FlyPokeModel.h"
#include "../Views/FlyPokeView.h"

class FlyPokeController : public BasePokeController<FlyPokeModel, FlyPokeView>
{
public:
    FlyPokeController(std::shared_ptr<FlyPokeModel> model) : BasePokeController(model)
    {
    }
};

