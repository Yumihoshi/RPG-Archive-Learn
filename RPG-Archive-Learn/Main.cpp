#include <iostream>
#include <Windows.h>
#include "FirePokeModel.h"
#include "IcePokeModel.h"
#include "GrassPokeModel.h"
#include "FlyPokeModel.h"
#include "GhostPokeModel.h"
#include "Common.h"
#include "PokeManager.h"
#include "FirePokeController.h"
#include "IcePokeController.h"
#include "GrassPokeController.h"
#include "FlyPokeController.h"
#include "GhostPokeController.h"



int main()
{
    SetConsoleOutputCP(65001);
    auto& pm = PokeManager::GetInstance();
    // 模型
    FirePokeModel f(pm.GetPokeDefaultNameByElement(ElementType::Fire), CampType::Friend);
    IcePokeModel i(pm.GetPokeDefaultNameByElement(ElementType::Ice), CampType::Friend);
    GrassPokeModel g(pm.GetPokeDefaultNameByElement(ElementType::Grass), CampType::Friend);
    FlyPokeModel f1(pm.GetPokeDefaultNameByElement(ElementType::Fly), CampType::Friend);
    GhostPokeModel g1(pm.GetPokeDefaultNameByElement(ElementType::Ghost), CampType::Friend);
    // 控制器
    FirePokeController fc(std::make_shared<FirePokeModel>(f));
    IcePokeController ic(std::make_shared<IcePokeModel>(i));
    GrassPokeController gc(std::make_shared<GrassPokeModel>(g));
    GhostPokeController gc1(std::make_shared<GhostPokeModel>(g1));
    FlyPokeController fc1(std::make_shared<FlyPokeModel>(f1));

    // 测试
    fc.ViewPtr->ShowPokeInfo();
    ic.ViewPtr->ShowPokeInfo();
    gc.ViewPtr->ShowPokeInfo();
    gc1.ViewPtr->ShowPokeInfo();
    fc1.ViewPtr->ShowPokeInfo();
    
    return 0;
}
