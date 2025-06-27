#include <windows.h>
#include "../../include/Managers/GameManager.h"

GameManager::GameManager() = default;

void GameManager::Init()
{
    // 设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
}
