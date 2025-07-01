#pragma once

#include "BasePokeModel.h"
#include "../../../Skills/NormalAttackSkill.h"

class BossPokeModel : public BasePokeModel
{
public:
    BossPokeModel(std::string name, CampType camp) : BasePokeModel(std::move(name), ElementType::None,
        200, 100, 10, camp, 100, 10, 0.25f, 0.1f, 50) // Example stats for a boss
    {
        SetStory("天星队的最终BOSS，仙后！");
        AddSkill(std::make_shared<NormalAttackSkill>());
    }
};