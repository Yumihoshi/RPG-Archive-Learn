/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午2:39
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_EQUIPMANAGER_H
#define RPG_EQUIPMANAGER_H

#include "../Base/Singleton.h"

class EquipManager : public Singleton<EquipManager>
{
public:

private:
    EquipManager() = default;
    friend class Singleton<EquipManager>;
};


#endif //RPG_EQUIPMANAGER_H
