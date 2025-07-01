#pragma once

#include <iostream>
#include <memory>
#include "../Common/Types.h"

class BasePokeModel;

class BaseEquipment
{
public:
    unsigned int Id;
    static unsigned int NextId;
	std::string Name;
	EquipType EqType;
	std::shared_ptr<BasePokeModel> Owner;
	virtual void ShowInfo() = 0;
    virtual void ApplyEffect() = 0;
    virtual void RemoveEffect() = 0;
    BaseEquipment() = default;
	explicit BaseEquipment(std::string name, EquipType type);

    virtual void to_json(json& j) const;
    friend void from_json(const json& j, BaseEquipment& p);
};

