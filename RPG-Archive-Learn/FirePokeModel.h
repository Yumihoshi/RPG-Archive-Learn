#pragma once

#include "BasePokeModel.h"
#include "Types.h"

class FirePokeModel : public BasePokeModel
{
public:
    FirePokeModel(std::string name, CampType camp ): BasePokeModel(name, ElementType::Fire,
            120, 30, 5, camp, 100, 10l, 0.2, 0.1, 8 )
    {
        
    }
private:
};

