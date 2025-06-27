#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../Models/GrassPokeModel.h"

class GrassPokeView : public BasePokeView<GrassPokeModel>
{
public:
    explicit GrassPokeView(std::shared_ptr<GrassPokeModel> model) : BasePokeView(std::move(model))
    {
    }
};

