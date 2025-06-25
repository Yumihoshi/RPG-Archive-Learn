#pragma once
#include <iostream>

class BaseEquipment
{
public:
	std::string name;
	virtual void showinfo() = 0;
};

