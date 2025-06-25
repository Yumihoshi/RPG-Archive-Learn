#include <iomanip>
#include "windows.h"
#include "LogManager.h"


/// <summary>
/// 打印回合开始
/// </summary>
void LogManager::PrintTurnStart()
{
    PrintByChar("============回合开始============\n");
}

/// <summary>
/// 打印回合结束
/// </summary>
void LogManager::PrintTurnEnd()
{
    PrintByChar("============回合结束============\n");
}

/// <summary>
/// 逐字输出
/// </summary>
void LogManager::PrintByChar(std::string text, int delayMs)
{
    std::cout << std::fixed << std::setprecision(2);
    for (char c : text)
    {
        std::cout << c << std::flush;  // 立即刷新缓冲区
        Sleep(delayMs);               // 暂停指定毫秒
    }
}

void LogManager::PrintByChar(std::string text, LogColor color)
{
    switch (color)
    {
    case LogColor::Red:
        PrintByChar(RED_CODE + text + END_CODE);
        break;
    case LogColor::Green:
        PrintByChar(GREEN_CODE + text + END_CODE);
        break;
    case LogColor::Yellow:
        PrintByChar(YELLOW_CODE + text + END_CODE);
        break;
    case LogColor::Blue:
        PrintByChar(BLUE_CODE + text + END_CODE);
        break;
    case LogColor::Purple:
        PrintByChar(PURPLE_CODE + text + END_CODE);
        break;
    default:
        PrintByChar(text);
        break;
    }
}

void LogManager::PrintByCharWithFlash(std::string text)
{
    PrintByChar(FLASH_CODE + text + END_CODE);
}

LogManager::LogManager() = default;
