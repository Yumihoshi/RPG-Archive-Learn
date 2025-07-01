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
    // 根据当前用户权限类型，显示不同的菜单
    void ShowCurUserSpecificMenu();
private:
    // 显示所有用户信息
    void ShowAllUsersInfo();
    void ShowAdminMenu();
    void ShowAdminUserPokeManagerMenu(const std::shared_ptr<UserModel>& user);
    void ShowModifyPokeMenu(const std::shared_ptr<UserModel>& user);
    void ShowPlayerMenu();

    // 显示关卡选择
    void ShowLevelSelection();
    void ShowArchiveMenu();
    // 选择出战宝可梦
    void ShowSelectFightingPokeMenu();

    // 单例相关
    friend class Singleton<UIManager>;
    UIManager();
};

