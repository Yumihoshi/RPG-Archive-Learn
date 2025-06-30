#pragma once

#include <utility>

#include "BasePokeView.h"
#include "../../Models/Poke/IcePokeModel.h"

class IcePokeView : public BasePokeView
{
public:
    explicit IcePokeView(std::shared_ptr<IcePokeModel> model) : BasePokeView(std::move(model))
    {
    }

    void ShowPokeInfo() override;
};

