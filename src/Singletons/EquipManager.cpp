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

void EquipManager::equipPokemon(EquipType eType, const std::shared_ptr<Pokemon>& pokemon)
{
    switch (eType)
    {
        case EquipType::Accessory:
        {
            // For simplicity, create a new Armor. In a real game, this would come from inventory.
            std::shared_ptr<Armor> newArmor = std::make_shared<Armor>(
                    "铁壁护甲",
                    20, 0.02);
            if (pokemon->armor)
            {
                std::cout << pokemon->name << " 已经装备了 "
                          << pokemon->armor->name
                          << "。是否替换？(y/n): ";
                std::string confirm;
                std::getline(std::cin, confirm);
                if (confirm == "y")
                {
                    pokemon->armor->removeEffect(pokemon);
                    pokemon->armor = nullptr;
                }
            }
            pokemon->armor = newArmor;
            pokemon->armor->applyEffect(pokemon);
            std::cout << pokemon->name << " 装备了 " << pokemon->armor->name
                      << "。"
                      << std::endl;
            break;
        }
        case EquipType::Armor:
        {
            // For simplicity, create a new Accessory. In a real game, this would come from inventory.
            std::shared_ptr<Accessory> newAccessory = std::make_shared<Accessory>(
                    "力量手环", 5, 0, 0.05);
            if (pokemon->accessory)
            {
                std::cout << pokemon->name << " 已经装备了 "
                          << pokemon->accessory->name << "。是否替换？(y/n): ";
                std::string confirm;
                std::getline(std::cin, confirm);
                if (confirm == "y")
                {
                    pokemon->accessory->removeEffect(pokemon);
                    pokemon->accessory = nullptr;
                }
            }
            pokemon->accessory = newAccessory;
            pokemon->accessory->applyEffect(pokemon);
            std::cout << pokemon->name << " 装备了 " << pokemon->accessory->name
                      << "。" << std::endl;
            break;
        }
    }
}

void EquipManager::unequipPokemon(EquipType eType, const std::shared_ptr<Pokemon>& pokemon)
{
    switch (eType)
    {
        case EquipType::Accessory:
            if (pokemon->armor)
            {
                pokemon->armor->removeEffect(pokemon);
                std::cout << pokemon->name << " 卸下了 " << pokemon->armor->name
                          << "。" << std::endl;
                pokemon->armor = nullptr;
            }
            else
            {
                std::cout << pokemon->name << " 没有装备防具。" << std::endl;
            }
            break;
        case EquipType::Armor:
            if (pokemon->accessory)
            {
                pokemon->accessory->removeEffect(pokemon);
                std::cout << pokemon->name << " 卸下了 "
                          << pokemon->accessory->name
                          << "。" << std::endl;
                pokemon->accessory = nullptr;
            }
            else
            {
                std::cout << pokemon->name << " 没有装备饰品。" << std::endl;
            }
            break;
    }
}
