#pragma once

#include "BasePokeController.h"
#include "IcePokeModel.h"
#include "IcePokeView.h"

class IcePokeController : public BasePokeController<IcePokeModel, IcePokeView>
{
public:
    IcePokeController(std::shared_ptr<IcePokeModel> model) : BasePokeController(model)
    {
    }
};

