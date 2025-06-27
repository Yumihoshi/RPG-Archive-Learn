#pragma once

#include "BasePokeView.h"
#include "../Models/FlyPokeModel.h"

class FlyPokeView : public BasePokeView<FlyPokeModel>
{
public:
    FlyPokeView(std::shared_ptr<FlyPokeModel> model) : BasePokeView(model)
    {
    }
};

