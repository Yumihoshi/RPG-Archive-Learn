#pragma once

#include "BasePokeModel.h"

class IcePokeModel : public BasePokeModel
{
public:
    IcePokeModel(std::string name,CampType camp) : BasePokeModel(name, ElementType::Ice, 
        100, 50, 10, camp, 100, 10, 0.15f, 0.1f, 10)
    {

    }

    void TakeDamage(int amount) override;
private:
    int _defendValue = 15;        // 魔法盾防御值
    bool CheckFlee();
};

