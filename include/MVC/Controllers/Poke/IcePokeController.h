#pragma once

#include <utility>

#include "BasePokeController.h"
#include "../../Models/Poke/IcePokeModel.h"
#include "../../Views/Poke/IcePokeView.h"

class IcePokeController : public BasePokeController
{
public:
    explicit IcePokeController(std::shared_ptr<IcePokeModel> model) : BasePokeController(std::move(model))
    {
    }
};

