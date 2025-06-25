#pragma once

#include "Singleton.h"

class EquipManager : public Singleton<EquipManager>
{
private:
    friend class Singleton<EquipManager>;
    EquipManager();
};

