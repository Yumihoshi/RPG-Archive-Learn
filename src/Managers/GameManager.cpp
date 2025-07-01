#include <windows.h>
#include "../../include/Managers/GameManager.h"
#include "../../include/Managers/FightManager.h"

GameManager::GameManager() = default;

#include "../../include/Managers/LevelManager.h"
#include "../../include/Managers/DialogueManager.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/EquipManager.h"

void GameManager::Init()
{
    // 设置控制台输出编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    FightManager::GetInstance().Init();
    LevelManager::GetInstance().Init();
    DialogueManager::GetInstance().Init();
    PokeManager::GetInstance().Init();
    EquipManager::GetInstance().Init();
}
