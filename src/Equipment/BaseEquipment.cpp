#include <utility>

#include "../../include/Equipment/BaseEquipment.h"

unsigned int BaseEquipment::NextId = 1;

BaseEquipment::BaseEquipment(std::string name, EquipType type)
{
    Name = std::move(name);
    Id = NextId++;
    EqType = type;
}

void BaseEquipment::to_json(json& j) const {
    j = json{
        {"Id", Id},
        {"Name", Name},
        {"EqType", EqType}
    };
}

void from_json(const json& j, BaseEquipment& p) {
    j.at("Id").get_to(p.Id);
    j.at("Name").get_to(p.Name);
    j.at("EqType").get_to(p.EqType);
}
