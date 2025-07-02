/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午2:39
* @version: 1.0
* @description: 
*******************************************************************************/
#include "../../include/Singletons/EquipManager.h"
#include "../../include/Equip/Armor.h"
#include "../../include/Equip/Accessory.h"

void EquipManager::equipPokemon(const std::shared_ptr<Equipment>& equipment, const std::shared_ptr<Pokemon>& pokemon)
{
    if (equipment->type == Equipment::ACCESSORY)
    {
        std::shared_ptr<Accessory> newAccessory = std::dynamic_pointer_cast<Accessory>(equipment);
        if (pokemon->accessory)
        {
            pokemon->accessory->removeEffect(pokemon);
        }
        pokemon->accessory = newAccessory;
        pokemon->accessory->applyEffect(pokemon);
        std::cout << pokemon->name << " 装备了 " << pokemon->accessory->name << "。" << std::endl;
    }
    else if (equipment->type == Equipment::ARMOR)
    {
        std::shared_ptr<Armor> newArmor = std::dynamic_pointer_cast<Armor>(equipment);
        if (pokemon->armor)
        {
            pokemon->armor->removeEffect(pokemon);
        }
        pokemon->armor = newArmor;
        pokemon->armor->applyEffect(pokemon);
        std::cout << pokemon->name << " 装备了 " << pokemon->armor->name << "。" << std::endl;
    }
}

void EquipManager::unequipPokemon(EquipType eType, const std::shared_ptr<Pokemon>& pokemon)
{
    if (eType == EquipType::Accessory)
    {
        if (pokemon->accessory)
        {
            pokemon->accessory->removeEffect(pokemon);
            std::cout << pokemon->name << " 卸下了 " << pokemon->accessory->name << "。" << std::endl;
            pokemon->accessory = nullptr;
        }
        else
        {
            std::cout << pokemon->name << " 没有装备饰品。" << std::endl;
        }
    }
    else if (eType == EquipType::Armor)
    {
        if (pokemon->armor)
        {
            pokemon->armor->removeEffect(pokemon);
            std::cout << pokemon->name << " 卸下了 " << pokemon->armor->name << "。" << std::endl;
            pokemon->armor = nullptr;
        }
        else
        {
            std::cout << pokemon->name << " 没有装备防具。" << std::endl;
        }
    }
}
