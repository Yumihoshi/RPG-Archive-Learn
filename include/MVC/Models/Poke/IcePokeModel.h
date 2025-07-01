#pragma once

#include <utility>

#include "BasePokeModel.h"

class IcePokeModel : public BasePokeModel
{
public:
    IcePokeModel() = default;
    IcePokeModel(std::string name, CampType camp) : BasePokeModel(std::move(name), ElementType::Ice,
        100, 50, 10, camp, 100, 10, 0.15f, 0.1f, 10)
    {
        _defendValue = 5;
        SetStory("拥有防御力，魔法值恢复较快。");
        AddSkill(std::make_shared<NormalAttackSkill>());
    }

    void TakeDamage(int amount) override;
    int GetDefendValue() const;
protected:
    void PerturbAttribute() override;
private:
    int _defendValue;        // 魔法盾防御值
};

