#include <windows.h>
#include "LogManager.h"
using namespace std;

/// <summary>
/// 打印回合开始
/// </summary>
void LogManager::PrintTurnStart()
{
    PrintByChar("======回合开始======\n");
}

/// <summary>
/// 打印回合结束
/// </summary>
void LogManager::PrintTurnEnd()
{
    PrintByChar("======回合结束======\n");
}

/// <summary>
/// 逐字输出
/// </summary>
void LogManager::PrintByChar(const std::string& text, int delayMs)
{
    for (char c : text)
    {
        cout << c << std::flush;  // 立即刷新缓冲区
        Sleep(delayMs);               // 暂停指定毫秒
    }
}

LogManager::LogManager() = default;
