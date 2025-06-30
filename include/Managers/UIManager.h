#pragma once

#include "../Base/Singleton.h"
#include "../MVC/Models/Poke/BasePokeModel.h"


class UIManager : public Singleton<UIManager>
{
public:
    // 显示宝可梦管理主菜单
    void ShowPokeManagerMainMenu();
    // 显示所有宝可梦信息
    void ShowAllPokesInfo();
    // 显示装备管理菜单
    void ShowEquipManagerMenu(const std::shared_ptr<BasePokeModel>& model);
private:
    friend class Singleton<UIManager>;
    UIManager();

    void HandleUserInput();
};

