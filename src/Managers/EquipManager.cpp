#include "../../include/Managers/EquipManager.h"
#include "../../include/Managers/LogManager.h"
#include "../../include/Equipment/Armor.h"
#include "../../include/Equipment/Decoration.h"

void EquipManager::Init()
{
    // Add some dummy equipment for testing
    auto armor1 = std::make_shared<Armor>("铁甲", 10, 0.05f);
    auto decoration1 = std::make_shared<Decoration>("力量之戒", 5, 0, 0.02f, 0.0f);

    _allEquipment[armor1->Id] = armor1;
    _allEquipment[decoration1->Id] = decoration1;
}

void EquipManager::Equip(const std::shared_ptr<BasePokeModel>& poke, unsigned int equipId, EquipType type)
{
    auto it = _allEquipment.find(equipId);
    if (it == _allEquipment.end())
    {
        LogManager::PrintByChar("Equipment with ID " + std::to_string(equipId) + " not found.\n", LogColor::Red);
        return;
    }

    auto equipment = it->second;

    if (equipment->EqType != type)
    {
        LogManager::PrintByChar("Equipment type mismatch.\n", LogColor::Red);
        return;
    }

    if (type == EquipType::Armor)
    {
        auto armor = std::dynamic_pointer_cast<Armor>(equipment);
        if (armor)
        {
            poke->Equip(armor);
            LogManager::PrintByChar("Equipped " + armor->Name + " to " + poke->GetName() + "\n");
        }
    }
    else if (type == EquipType::Decoration)
    {
        auto decoration = std::dynamic_pointer_cast<Decoration>(equipment);
        if (decoration)
        {
            poke->Equip(decoration);
            LogManager::PrintByChar("Equipped " + decoration->Name + " to " + poke->GetName() + "\n");
        }
    }
}

void EquipManager::Unequip(const std::shared_ptr<BasePokeModel>& poke, EquipType type)
{
    poke->Unequip(type);
    LogManager::PrintByChar("Unequipped item from " + poke->GetName() + "\n");
}
