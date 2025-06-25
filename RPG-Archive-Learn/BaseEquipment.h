#pragma once

#include <iostream>
#include "BasePokeModel.h"

class BaseEquipment
{
public:
	std::string Name;
	std::shared_ptr<BasePokeModel> Owner;
	virtual void showinfo() = 0;
};

