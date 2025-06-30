#include <iostream>
#include <Windows.h>
#include "../include/MVC/Models/Poke/FirePokeModel.h"
#include "../include/MVC/Models/Poke/IcePokeModel.h"
#include "../include/MVC/Models/Poke/GrassPokeModel.h"
#include "../include/MVC/Models/Poke/FlyPokeModel.h"
#include "../include/MVC/Models/Poke/GhostPokeModel.h"
#include "../include/Common/Common.h"
#include "../include/Managers/PokeManager.h"
#include "../include/MVC/Controllers/Poke/FirePokeController.h"
#include "../include/MVC/Controllers/Poke/IcePokeController.h"
#include "../include/MVC/Controllers/Poke/GrassPokeController.h"
#include "../include/MVC/Controllers/Poke/FlyPokeController.h"
#include "../include/MVC/Controllers/Poke/GhostPokeController.h"
#include "../include/Managers/GameManager.h"
#include "../include/Managers/FightManager.h"
#include "../include/Base/Singleton.h"
#include "../include/MVC/Views/User/UserView.h"
#include "../include/Managers/UserManager.h"


#define TEST_POKE false
#define TEST_USER false
#define TEST_FIGHT false


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
        std::cout << "\n===== 用户系统 =====\n";

        auto &userManager = UserManager::GetInstance();
        auto view = std::make_shared<UserView>();
        view->ShowLoginMenu();
        std::string choice;
        std::cin >> choice;

        if (choice == "1")
        {
            userManager.RegisterUser();
        }
        else if (choice == "2")
        {
            if (userManager.LoginUser())
            {
                // 登录后的操作
                std::cout << userManager.GetCurUser().GetPassword() << std::endl;
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
