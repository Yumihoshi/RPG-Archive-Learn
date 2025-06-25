#include <iostream>
#include "IcePokeModel.h"
#include "LogManager.h"

void IcePokeModel::TakeDamage(int amount)
{
    auto& logger = LogManager::GetInstance();
    // 闪避逻辑
    if (BasePokeModel::CheckFlee())
    {
        logger.PrintByChar(_name + "触发了");
        logger.PrintByChar("闪避", LogColor::Yellow);
        logger.PrintByChar("！\n");
        return;
    }
    else
    {
        BasePokeModel::TakeDamage(amount - _defendValue);
    }
}
