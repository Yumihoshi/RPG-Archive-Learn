#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../Models/FirePokeModel.h"
#include "../Views/FirePokeView.h"

class FirePokeController : public BasePokeController
{
public:
    explicit FirePokeController(std::shared_ptr<FirePokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

