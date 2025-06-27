#pragma once

#include "../Base/Singleton.h"

class UIManager : public Singleton<UIManager>
{
private:
    friend class Singleton<UIManager>;
    UIManager();
};

