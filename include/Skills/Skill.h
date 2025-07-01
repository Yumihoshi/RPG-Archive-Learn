#pragma once

#include <string>
#include <memory>
#include "../MVC/Models/Poke/BasePokeModel.h"

class Skill
{
public:
    std::string Name;
    std::string Description;
    int MpCost;

    Skill(std::string name, std::string description, int mpCost);
    virtual ~Skill() = default;

    virtual void Use(const std::shared_ptr<BasePokeModel>& user, const std::shared_ptr<BasePokeModel>& target) = 0;
};