#include <utility>

#include "../../include/Equipment/BaseEquipment.h"

BaseEquipment::BaseEquipment(std::string name)
{
    Name = std::move(name);
}
