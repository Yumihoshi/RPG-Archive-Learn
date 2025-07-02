#include "../../include/Equip/Equipment.h"
#include "../../include/Poke/Pokemon.h"
#include <iostream>
#include <nlohmann/json.hpp>

// Base Equipment class implementation
Equipment::Equipment(std::string name, Type type) :
        name(name),
        type(type)
{}
