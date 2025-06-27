#pragma once

#include <iostream>
#include <memory>
class BasePokeModel;

class BaseEquipment
{
public:
	std::string Name;
	std::shared_ptr<BasePokeModel> Owner;
	virtual void ShowInfo() = 0;
	explicit BaseEquipment(std::string name);
};

