#pragma once

#include "../Base/Singleton.h"

class GameManager : public Singleton<GameManager>
{
private:
    friend class Singleton<GameManager>;
    GameManager();
};

