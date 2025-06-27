#pragma once

#include <map>
#include <vector>
#include "../Base/Singleton.h"
#include "../Common/Types.h"
#include "../Equipment/BaseEquipment.h"

class EquipManager : public Singleton<EquipManager>
{
public:
    // 添加装备
    bool AddEquipment(EquipType type, std::shared_ptr<BaseEquipment> equipment);

    // 删除装备
    bool RemoveEquipmentByType(EquipType type);

    // 根据类别获取装备
    [[nodiscard]] std::shared_ptr<BaseEquipment> GetEquipmentByType(EquipType type) const;

    // 根据名称获取装备
    [[nodiscard]] std::shared_ptr<BaseEquipment> GetEquipmentByName(const std::string& name) const;

    // 检查装备是否存在
    [[nodiscard]] bool HasEquipment(EquipType type) const;

    // 获取所有装备类型
    [[nodiscard]] std::vector<EquipType> GetAllEquipTypes() const;

    // 清空所有装备
    void ClearAll();
private:
    std::map<EquipType, std::shared_ptr<BaseEquipment>> _equipMap;
    
private:
    friend class Singleton<EquipManager>;
    EquipManager();
};

