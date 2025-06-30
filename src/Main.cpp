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
#include "../include/Managers/UserManager.h"
#include "../include/Managers/GameManager.h"
#include "../include/Managers/FightManager.h"


#define TEST_POKE false
#define TEST_USER false
#define TEST_FIGHT true


int main()
{
    GameManager::GetInstance().Init();
#if TEST_POKE
    auto &pm = PokeManager::GetInstance();
    // 模型
    FirePokeModel f(pm.GetPokeDefaultNameByElement(ElementType::Fire),
                    CampType::Friend);
    IcePokeModel i(pm.GetPokeDefaultNameByElement(ElementType::Ice),
                   CampType::Friend);
    GrassPokeModel g(pm.GetPokeDefaultNameByElement(ElementType::Grass),
                     CampType::Friend);
    FlyPokeModel f1(pm.GetPokeDefaultNameByElement(ElementType::Fly),
                    CampType::Friend);
    GhostPokeModel g1(pm.GetPokeDefaultNameByElement(ElementType::Ghost),
                      CampType::Friend);
    f.Init();
    i.Init();
    g.Init();
    f1.Init();
    g1.Init();
    // 控制器
    FirePokeController fc(std::make_shared<FirePokeModel>(f));
    IcePokeController ic(std::make_shared<IcePokeModel>(i));
    GrassPokeController gc(std::make_shared<GrassPokeModel>(g));
    GhostPokeController gc1(std::make_shared<GhostPokeModel>(g1));
    FlyPokeController fc1(std::make_shared<FlyPokeModel>(f1));

    PokeManager::GetInstance().AddPoke(ElementType::Fire,
                                       std::make_shared<FirePokeModel>(f));
    auto ss = PokeManager::GetInstance().GetPokeByName(f.GetName());
    std::cout << ss->GetName() << std::endl;
#endif

#if TEST_USER
    while (true)
    {
        std::cout << "\n===== 用户系统 =====\n"
             << "1. 注册\n"
             << "2. 登录\n"
             << "3. 退出\n"
             << "请选择: ";

        std::string choice;
        getline(std::cin, choice);

        if (choice == "1")
        {
            UserManager::GetInstance().RegisterUser();
        }
        else if (choice == "2")
        {
            if (UserManager::GetInstance().LoginUser())
            {
                // 登录后的操作
                std::cout << "\n欢迎进入系统！\n";
                break;
            }
        }
        else if (choice == "3")
        {
            std::cout << "系统已退出！\n";
            break;
        }
        else
        {
            std::cout << "无效选择，请重新输入！\n";
        }
    }
#endif

#if TEST_FIGHT
    auto &pm = PokeManager::GetInstance();
    auto &fm = FightManager::GetInstance();
    fm.SetPlayerFightPoke(std::make_shared<FlyPokeModel>(
                    pm.GetPokeDefaultNameByElement(ElementType::Fly),
                    CampType::Friend));
    fm.SetEnemyFightPoke(std::make_shared<GhostPokeModel>(
                    pm.GetPokeDefaultNameByElement(ElementType::Ghost),
                    CampType::Enemy));
    fm.Init();
    fm.StartFight();
#endif

    return 0;
}
