#pragma once

#include <iostream>
class BasePokeModel;

class BaseEquipment
{
public:
	std::string Name;
	std::shared_ptr<BasePokeModel> Owner;
	virtual void ShowInfo() = 0;
	BaseEquipment(std::string name);
};

