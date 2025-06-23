#pragma once

#include <iostream>
#include "Singleton.h"

using namespace std;

class Common : public Singleton<Common>
{
public:
    static string GetFormattedFloat(float num, int wei = 2);
};

