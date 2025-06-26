#pragma once

#include <iostream>
#include <random>
#include "Singleton.h"


class Common : public Singleton<Common>
{
public:
    std::string GetFormattedFloat(float num, int wei = 2);
    float GetRandomFloat(float min, float max);
private:
    friend class Singleton<Common>;
    Common();
private:
    std::random_device _rd;
    std::mt19937 _gen;
};

