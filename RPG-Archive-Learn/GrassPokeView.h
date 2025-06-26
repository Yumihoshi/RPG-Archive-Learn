#pragma once

#include "BasePokeView.h"
#include "GrassPokeModel.h"

class GrassPokeView : public BasePokeView<GrassPokeModel>
{
public:
    GrassPokeView(std::shared_ptr<GrassPokeModel> model) : BasePokeView(model)
    {
    }
};

