#include <iostream>
#include <Windows.h>
#include "FirePokeModel.h"
#include "IcePokeModel.h"
#include "GrassPokeModel.h"
#include "FlyPokeModel.h"
#include "GhostPokeModel.h"
#include "Common.h"


int main()
{
    SetConsoleOutputCP(65001);
    FirePokeModel f("火火火", CampType::Friend);
    IcePokeModel i("冰冰冰", CampType::Friend);
    GrassPokeModel g("草草草", CampType::Friend);
    FlyPokeModel f1("飞飞飞", CampType::Friend);
    GhostPokeModel g1("鬼鬼鬼", CampType::Friend);

    return 0;
}
