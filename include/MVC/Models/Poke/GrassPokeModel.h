#pragma once

#include <utility>

#include "BasePokeModel.h"

class GrassPokeModel : public BasePokeModel
{
public:
    GrassPokeModel(std::string name, CampType camp) : BasePokeModel(std::move(name), ElementType::Grass,
        100, 65, 5, camp, 100, 10, 0.15f, 0.1f, 10)
    {
        SetStory("拥有回血技能。");
        AddSkill(std::make_shared<NormalAttackSkill>());
    }
private:
};

