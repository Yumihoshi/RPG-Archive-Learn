#pragma once

#include "../Base/Singleton.h"
#include "../MVC/Models/User/UserModel.h"

class GameManager : public Singleton<GameManager>
{
public:
    std::shared_ptr<UserModel> AdminSelectedUser;
public:
    // 游戏初始化
    void Init();
private:
    friend class Singleton<GameManager>;
    GameManager();
};

