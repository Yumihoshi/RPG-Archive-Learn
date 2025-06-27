#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../Models/IcePokeModel.h"
#include "../Views/IcePokeView.h"

class IcePokeController : public BasePokeController<IcePokeModel, IcePokeView>
{
public:
    explicit IcePokeController(std::shared_ptr<IcePokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

