#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../../Models/Poke/FlyPokeModel.h"
#include "../../Views/Poke/FlyPokeView.h"

class FlyPokeController : public BasePokeController
{
public:
    explicit FlyPokeController(std::shared_ptr<FlyPokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

