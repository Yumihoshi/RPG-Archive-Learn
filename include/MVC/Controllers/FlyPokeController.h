#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../Models/FlyPokeModel.h"
#include "../Views/FlyPokeView.h"

class FlyPokeController : public BasePokeController
{
public:
    explicit FlyPokeController(std::shared_ptr<FlyPokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

