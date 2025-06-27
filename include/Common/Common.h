#pragma once

#include <iostream>
#include <random>
#include "../Base/Singleton.h"
#include "Types.h"


class Common : public Singleton<Common>
{
public:
    static std::string GetFormattedFloat(float num, int wei = 2);
    static float GetRandomFloat(float min, float max);
    static std::string GetElementName(ElementType type);
private:
    friend class Singleton<Common>;
    Common();
private:
    static std::random_device _rd;
    static std::mt19937 _gen;
};

