#pragma once
#include "BasePokeModel.h"
class GhostPokeModel :public BasePokeModel
{
	GhostPokeModel(std::string name, CampType camp ) :BasePokeModel(name, ElementType::Ghost,	
			80, 50, 5, camp, 100, 10, 0.15, 0.3, 10)
	{

	}

};
