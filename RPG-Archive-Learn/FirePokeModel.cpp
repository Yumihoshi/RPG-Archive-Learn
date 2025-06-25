#include "FirePokeModel.h"
#include "LogManager.h"

void FirePokeModel::TakeDamage(int amount)
{
    auto& logger = LogManager::GetInstance();
    // 闪避
    if (BasePokeModel::CheckFlee())
    {
        logger.PrintByChar(_name + "触发了");
        logger.PrintByChar("闪避", LogColor::Yellow);
        logger.PrintByChar("！\n");
        return;
    }
    else
    {
        BasePokeModel::TakeDamage(amount);
    }
}
