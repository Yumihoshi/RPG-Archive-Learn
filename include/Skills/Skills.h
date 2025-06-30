//
// Created by ASUS on 25-6-30.
//

#ifndef SKILLS_H
#define SKILLS_H
#include "../Common/Types.h"
#include "../MVC/Models/BasePokeModel.h"

class SkillHandler {
public:
    void useSkill(Skills skill, BasePokeModel& user);
};




#endif //SKILLS_H
