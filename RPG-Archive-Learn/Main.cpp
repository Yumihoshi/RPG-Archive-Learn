#include <iostream>
#include <Windows.h>
#include "FirePokeModel.h"
#include "IcePokeModel.h"
#include "GrassPokeModel.h"
#include "FlyPokeModel.h"
#include "GhostPokeModel.h"
#include "Common.h"
#include "PokeManager.h"
#include "FirePokeView.h"
#include "IcePokeView.h"
#include "GrassPokeView.h"
#include "FlyPokeView.h"
#include "GhostPokeView.h"



int main()
{
    SetConsoleOutputCP(65001);
    auto& pm = PokeManager::GetInstance();
    FirePokeModel f(pm.GetPokeDefaultNameByElement(ElementType::Fire), CampType::Friend);
    IcePokeModel i(pm.GetPokeDefaultNameByElement(ElementType::Ice), CampType::Friend);
    GrassPokeModel g(pm.GetPokeDefaultNameByElement(ElementType::Grass), CampType::Friend);
    FlyPokeModel f1(pm.GetPokeDefaultNameByElement(ElementType::Fly), CampType::Friend);
    GhostPokeModel g1(pm.GetPokeDefaultNameByElement(ElementType::Ghost), CampType::Friend);

    FirePokeView fv(std::make_shared<FirePokeModel>(f));
    IcePokeView iv(std::make_shared<IcePokeModel>(i));
    GrassPokeView gv(std::make_shared<GrassPokeModel>(g));
    GhostPokeView gv1(std::make_shared<GhostPokeModel>(g1));
    FlyPokeView fv1(std::make_shared<FlyPokeModel>(f1));
    fv.ShowPokeInfo();
    iv.ShowPokeInfo();
    gv.ShowPokeInfo();
    gv1.ShowPokeInfo();
    fv1.ShowPokeInfo();
    
    return 0;
}
