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

    static void PrintByChar(const std::string& text, LogColor color);

    static void PrintByCharWithFlash(const std::string& text);

private:
    friend class Singleton<LogManager>;
    LogManager();

    static const std::string RED_CODE;
    static const std::string GREEN_CODE;
    static const std::string YELLOW_CODE;
    static const std::string BLUE_CODE;
    static const std::string PURPLE_CODE;
    static const std::string END_CODE;

    static const std::string FLASH_CODE;
};

