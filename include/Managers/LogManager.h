#pragma once

#include <iostream>
#include "../Base/Singleton.h"


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
    static void PrintTurnStart();

    /// <summary>
    /// 打印回合结束
    /// </summary>
    static void PrintTurnEnd();

    /// <summary>
    /// 逐字输出
    /// </summary>
    static void PrintByChar(const std::string& text, int delayMs = 30);

    void PrintByChar(const std::string& text, LogColor color);

    void PrintByCharWithFlash(const std::string& text);

private:
    friend class Singleton<LogManager>;
    LogManager();

    const std::string RED_CODE = "\033[31m";
    const std::string GREEN_CODE = "\033[32m";
    const std::string YELLOW_CODE = "\033[33m";
    const std::string BLUE_CODE = "\033[36m";
    const std::string PURPLE_CODE = "\033[35m";
    const std::string END_CODE = "\033[0m";

    const std::string FLASH_CODE = "\033[5m";
};

