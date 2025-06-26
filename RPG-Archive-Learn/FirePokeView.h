#pragma once

#include "BasePokeView.h"
#include "FirePokeModel.h"


class FirePokeView : public BasePokeView<FirePokeModel>
{
public:
    FirePokeView(std::shared_ptr<FirePokeModel> model) : BasePokeView(model)
    {
    }

private:
};

