#pragma once

#include <iostream>
#include "Singleton.h"


class Common : public Singleton<Common>
{
public:
    static std::string GetFormattedFloat(float num, int wei = 2);
};

