#pragma once

#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
private:
    friend class Singleton<GameManager>;
    GameManager();
};

