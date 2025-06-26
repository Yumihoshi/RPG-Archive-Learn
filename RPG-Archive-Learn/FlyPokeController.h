#pragma once

#include "BasePokeController.h"
#include "FlyPokeModel.h"
#include "FlyPokeView.h"

class FlyPokeController : public BasePokeController<FlyPokeModel, FlyPokeView>
{
public:
    FlyPokeController(std::shared_ptr<FlyPokeModel> model) : BasePokeController(model)
    {
    }
};

