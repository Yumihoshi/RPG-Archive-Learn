#pragma once

#include "BasePokeController.h"
#include "FirePokeModel.h"
#include "FirePokeView.h"

class FirePokeController : public BasePokeController<FirePokeModel, FirePokeView>
{
public:
    FirePokeController(std::shared_ptr<FirePokeModel> model) : BasePokeController(model)
    {
    }
};

