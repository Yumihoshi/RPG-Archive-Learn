#pragma once

#include "BasePokeModel.h"

class GrassPokeModel : public BasePokeModel
{
public:
    GrassPokeModel(std::string name,CampType camp ) : BasePokeModel(name, ElementType::Nature,
            100, 65, 5, camp, 100, 10, 0.15, 0.1, 10)
    {
    }
private:
};

