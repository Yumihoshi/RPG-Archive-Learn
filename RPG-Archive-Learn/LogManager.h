#pragma once
#include "Singleton.h"

class LogManager : public Singleton<LogManager>
{
public:
    /// <summary>
    /// 打印回合开始
    /// </summary>
    void PrintTurnStart();

    /// <summary>
    /// 打印回合结束
    /// </summary>
    void PrintTurnEnd();

    /// <summary>
    /// 逐字输出
    /// </summary>
    void PrintByChar(const std::string& text, int delayMs = 30);

private:
    friend class Singleton<LogManager>;
    LogManager();
};

