#pragma once

#include <map>
#include <vector>
#include "Singleton.h"
#include "Types.h"
#include "BaseEquipment.h"

class EquipManager : public Singleton<EquipManager>
{
public:
    // 添加装备
    bool AddEquipment(EquipType type, std::shared_ptr<BaseEquipment> equipment);

    // 删除装备
    bool RemoveEquipmentByType(EquipType type);

    // 根据类别获取装备
    std::shared_ptr<BaseEquipment> GetEquipmentByType(EquipType type) const;

    // 根据名称获取装备
    std::shared_ptr<BaseEquipment> GetEquipmentByName(std::string name) const;

    // 检查装备是否存在
    bool HasEquipment(EquipType type) const;

    // 获取所有装备类型
    std::vector<EquipType> GetAllEquipTypes() const;

    // 清空所有装备
    void ClearAll();
private:
    std::map<EquipType, std::shared_ptr<BaseEquipment>> _equipMap;
    // TODO: 根据ai的代码补全
private:
    friend class Singleton<EquipManager>;
    EquipManager();
};

