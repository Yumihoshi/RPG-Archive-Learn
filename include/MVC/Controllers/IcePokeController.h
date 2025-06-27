#pragma once

#include "BasePokeController.h"
#include "../Models/IcePokeModel.h"
#include "../Views/IcePokeView.h"

class IcePokeController : public BasePokeController<IcePokeModel, IcePokeView>
{
public:
    IcePokeController(std::shared_ptr<IcePokeModel> model) : BasePokeController(model)
    {
    }
};

