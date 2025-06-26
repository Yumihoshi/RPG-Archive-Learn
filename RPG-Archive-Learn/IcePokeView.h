#pragma once

#include "BasePokeView.h"
#include "IcePokeModel.h"

class IcePokeView : public BasePokeView<IcePokeModel>
{
public:
    IcePokeView(std::shared_ptr<IcePokeModel> model) : BasePokeView(model)
    {
    }

    void ShowPokeInfo() override;
};

