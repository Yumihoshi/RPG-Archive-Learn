#pragma once

#include "Singleton.h"

using namespace std;

enum class LogColor
{
    White,
    Red,
    Green,
    Yellow,
    Blue,
    Purple
};

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
    void PrintByChar(string text, int delayMs = 30);

    void PrintByChar(string text, LogColor color);

    void PrintByCharWithFlash(string text);

private:
    friend class Singleton<LogManager>;
    LogManager();

    const string RED_CODE = "\033[31m";
    const string GREEN_CODE = "\033[32m";
    const string YELLOW_CODE = "\033[33m";
    const string BLUE_CODE = "\033[36m";
    const string PURPLE_CODE = "\033[35m";
    const string END_CODE = "\033[0m";

    const string FLASH_CODE = "\033[5m";
};

