#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../Models/FirePokeModel.h"


class FirePokeView : public BasePokeView<FirePokeModel>
{
public:
    explicit FirePokeView(std::shared_ptr<FirePokeModel> model) : BasePokeView(std::move(model))
    {
    }

private:
};

