#pragma once
#include <iostream>
using namespace std;
class BaseEquipment
{
public:
	string name;
	virtual void showinfo() = 0;
};

