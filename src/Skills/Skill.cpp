#include "../../include/Skills/Skill.h"

Skill::Skill(std::string name, std::string description, int mpCost)
    : Name(std::move(name)), Description(std::move(description)), MpCost(mpCost)
{
}