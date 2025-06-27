#pragma once

#include "BasePokeView.h"
#include "../Models/GrassPokeModel.h"

class GrassPokeView : public BasePokeView<GrassPokeModel>
{
public:
    GrassPokeView(std::shared_ptr<GrassPokeModel> model) : BasePokeView(model)
    {
    }
};

