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
#include "../Common/Types.h"
#include "../Poke/Pokemon.h"
#include "../Equip/Equipment.h"

class EquipManager : public Singleton<EquipManager>
{
public:
    void equipPokemon(const std::shared_ptr<Equipment>& equipment, const std::shared_ptr<Pokemon>& pokemon);
    void unequipPokemon(EquipType eType, const std::shared_ptr<Pokemon>& pokemon);
private:
    EquipManager() = default;
    friend class Singleton<EquipManager>;
};


#endif //RPG_EQUIPMANAGER_H
