#include "../../include/Equip/Equipment.h"
#include "../../include/Poke/Pokemon.h"
#include <iostream>
#include <nlohmann/json.hpp>

// 装备构造函数
Equipment::Equipment(std::string name, Type type) :
        name(name),
        type(type)
{}
