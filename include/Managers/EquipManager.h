#pragma once

#include "../Base/Singleton.h"
#include "../MVC/Models/Poke/BasePokeModel.h"
#include "../Equipment/BaseEquipment.h"
#include <map>

class EquipManager : public Singleton<EquipManager>
{
public:
    void Equip(const std::shared_ptr<BasePokeModel>& poke, unsigned int equipId, EquipType type);
    void Unequip(const std::shared_ptr<BasePokeModel>& poke, EquipType type);
    void Init();

private:
    std::map<unsigned int, std::shared_ptr<BaseEquipment>> _allEquipment;
    friend class Singleton<EquipManager>;
    EquipManager() = default;
};