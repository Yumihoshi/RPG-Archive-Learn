#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../Models/FlyPokeModel.h"

class FlyPokeView : public BasePokeView
{
public:
    explicit FlyPokeView(std::shared_ptr<FlyPokeModel> model) : BasePokeView(std::move(model))
    {
    }
};

