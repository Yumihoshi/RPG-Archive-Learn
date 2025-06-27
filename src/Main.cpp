#include <iostream>
#include <Windows.h>
#include "../include/MVC/Models/FirePokeModel.h"
#include "../include/MVC/Models/IcePokeModel.h"
#include "../include/MVC/Models/GrassPokeModel.h"
#include "../include/MVC/Models/FlyPokeModel.h"
#include "../include/MVC/Models/GhostPokeModel.h"
#include "../include/Common/Common.h"
#include "../include/Managers/PokeManager.h"
#include "../include/MVC/Controllers/FirePokeController.h"
#include "../include/MVC/Controllers/IcePokeController.h"
#include "../include/MVC/Controllers/GrassPokeController.h"
#include "../include/MVC/Controllers/FlyPokeController.h"
#include "../include/MVC/Controllers/GhostPokeController.h"



int main()
{
    setbuf(stdout, nullptr);  // 禁用缓冲区，实时输出
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
    for (size_t i = 0; i < 50; i++)
    {
        ic.Attack(fc.ModelPtr);
    }
    
    fc.ViewPtr->ShowPokeInfo();
    ic.ViewPtr->ShowPokeInfo();

    /*gc.ViewPtr->ShowPokeInfo();
    gc1.ViewPtr->ShowPokeInfo();
    fc1.ViewPtr->ShowPokeInfo();*/
    
    return 0;
}
