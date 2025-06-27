#pragma once

#include "../Base/Singleton.h"

class GameManager : public Singleton<GameManager>
{
public:
    // 游戏初始化
    void Init();
private:
    friend class Singleton<GameManager>;
    GameManager();
};

