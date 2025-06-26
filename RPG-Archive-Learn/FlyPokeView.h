#pragma once

#include "BasePokeView.h"
#include "FlyPokeModel.h"

class FlyPokeView : public BasePokeView<FlyPokeModel>
{
public:
    FlyPokeView(std::shared_ptr<FlyPokeModel> model) : BasePokeView(model)
    {
    }
};

