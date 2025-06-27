#include "../../include/Managers/EquipManager.h"
#include "../../include/Equipment/BaseEquipment.h" // 确保包含基类定义

bool EquipManager::AddEquipment(EquipType type, std::shared_ptr<BaseEquipment> equipment)
{
    if (!equipment) return false; // 空指针检查

    // 插入或替换现有装备
    _equipMap[type] = std::move(equipment);
    return true;
}

bool EquipManager::RemoveEquipmentByType(EquipType type)
{
    return _equipMap.erase(type) > 0;
}

std::shared_ptr<BaseEquipment> EquipManager::GetEquipmentByType(EquipType type) const
{
    auto it = _equipMap.find(type);
    return (it != _equipMap.end()) ? it->second : nullptr;
}

bool EquipManager::HasEquipment(EquipType type) const
{
    return _equipMap.find(type) != _equipMap.end();
}

std::vector<EquipType> EquipManager::GetAllEquipTypes() const
{
    std::vector<EquipType> types;
    for (const auto& pair : _equipMap)
    {
        types.push_back(pair.first);
    }
    return types;
}

void EquipManager::ClearAll()
{
    _equipMap.clear();
}

// 根据名称获取装备
std::shared_ptr<BaseEquipment> EquipManager::GetEquipmentByName(std::string name) const
{
    for (const auto& pair : _equipMap)
    {
        if (pair.second->Name == name)
        {
            return pair.second;
        }
    }
    return nullptr;
}
