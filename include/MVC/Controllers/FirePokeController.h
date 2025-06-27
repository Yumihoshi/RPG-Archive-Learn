#pragma once

#include "BasePokeController.h"
#include "../Models/FirePokeModel.h"
#include "../Views/FirePokeView.h"

class FirePokeController : public BasePokeController<FirePokeModel, FirePokeView>
{
public:
    FirePokeController(std::shared_ptr<FirePokeModel> model) : BasePokeController(model)
    {
    }
};

