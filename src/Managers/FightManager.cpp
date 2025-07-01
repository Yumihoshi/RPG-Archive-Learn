/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午2:05
* @version: 1.0
* @description: 
*******************************************************************************/
#include <utility>

#include "../../include/Managers/FightManager.h"
#include "../../include/MVC/Controllers/Poke/FirePokeController.h"
#include "../../include/MVC/Controllers/Poke/IcePokeController.h"
#include "../../include/MVC/Controllers/Poke/GrassPokeController.h"
#include "../../include/MVC/Controllers/Poke/FlyPokeController.h"
#include "../../include/MVC/Controllers/Poke/GhostPokeController.h"
#include "../../include/Fight/PlayerFightState.h"
#include "../../include/Fight/EnemyFightState.h"
#include "../../include/Fight/DefaultFightState.h"


FightManager::FightManager() = default;


std::shared_ptr<BasePokeController> FightManager::GetPlayerFightPoke() const
{
    return _playerFightPoke;
}

std::shared_ptr<BasePokeController> FightManager::GetEnemyFightPoke() const
{
    return _enemyFightPoke;
}

void
FightManager::SetPlayerFightPoke(
        const std::shared_ptr<BasePokeModel> &playerModel)
{
    switch (playerModel->GetElement())
    {
        case ElementType::None:
        {
            LogManager::PrintByChar("错误：无效的元素类型");
            break;
        }
        case ElementType::Fire:
        {
            auto m = std::dynamic_pointer_cast<FirePokeModel>(playerModel);
            _playerFightPoke = std::make_shared<FirePokeController>(m);
            break;
        }
        case ElementType::Ice:
        {
            auto m = std::dynamic_pointer_cast<IcePokeModel>(playerModel);
            _playerFightPoke = std::make_shared<IcePokeController>(m);
            break;
        }
        case ElementType::Grass:
        {
            auto m = std::dynamic_pointer_cast<GrassPokeModel>(playerModel);
            _playerFightPoke = std::make_shared<GrassPokeController>(m);
            break;
        }
        case ElementType::Fly:
        {
            auto m = std::dynamic_pointer_cast<FlyPokeModel>(playerModel);
            _playerFightPoke = std::make_shared<FlyPokeController>(m);
            break;
        }
        case ElementType::Ghost:
        {
            auto m = std::dynamic_pointer_cast<GhostPokeModel>(playerModel);
            _playerFightPoke = std::make_shared<GhostPokeController>(m);
            break;
        }
    }
}

void FightManager::SetEnemyFightPoke(
        const std::shared_ptr<BasePokeModel> &enemyModel)
{
    switch (enemyModel->GetElement())
    {
        case ElementType::None:
        {
            LogManager::PrintByChar("错误：无效的元素类型");
            break;
        }
        case ElementType::Fire:
        {
            auto m = std::dynamic_pointer_cast<FirePokeModel>(enemyModel);
            _enemyFightPoke = std::make_shared<FirePokeController>(m);
            break;
        }
        case ElementType::Ice:
        {
            auto m = std::dynamic_pointer_cast<IcePokeModel>(enemyModel);
            _enemyFightPoke = std::make_shared<IcePokeController>(m);
            break;
        }
        case ElementType::Grass:
        {
            auto m = std::dynamic_pointer_cast<GrassPokeModel>(enemyModel);
            _enemyFightPoke = std::make_shared<GrassPokeController>(m);
            break;
        }
        case ElementType::Fly:
        {
            auto m = std::dynamic_pointer_cast<FlyPokeModel>(enemyModel);
            _enemyFightPoke = std::make_shared<FlyPokeController>(m);
            break;
        }
        case ElementType::Ghost:
        {
            auto m = std::dynamic_pointer_cast<GhostPokeModel>(enemyModel);
            _enemyFightPoke = std::make_shared<GhostPokeController>(m);
            break;
        }
    }
}

void FightManager::Init()
{
    _fightStateMachine = std::make_unique<StateMachine<FightRoundType>>();
    _fightStateMachine->AddState(FightRoundType::Default,
                                 std::make_unique<DefaultFightState>());
    _fightStateMachine->AddState(FightRoundType::Player,
                                 std::make_unique<PlayerFightState>());
    _fightStateMachine->AddState(FightRoundType::Enemy,
                                 std::make_unique<EnemyFightState>());
}

void FightManager::EnterPlayerRound()
{
    _fightStateMachine->SwitchState(FightRoundType::Player);
}

void FightManager::EnterEnemyRound()
{
    _fightStateMachine->SwitchState(FightRoundType::Enemy);
}

#include "../../include/Managers/LevelManager.h"
#include "../../include/Managers/PokeManager.h"
#include "../../include/Managers/DialogueManager.h"

// 开始战斗
void FightManager::StartFight()
{
    DialogueManager::GetInstance().ShowDialogue("battle_start");
    ShowFightStart();
    while (_playerFightPoke->ModelPtr->IsAlive() &&
           _enemyFightPoke->ModelPtr->IsAlive())
    {
        ShowFightInfo();
        EnterPlayerRound();
        if (_enemyFightPoke->ModelPtr->IsAlive()) EnterEnemyRound();
        EnterBlankRound();
    }
    if (!_playerFightPoke->ModelPtr->IsAlive())
    {
        DialogueManager::GetInstance().ShowDialogue("battle_lose");
        LogManager::PrintByChar("你输了！\n");
    }
    else
    {
        DialogueManager::GetInstance().ShowDialogue("battle_win");
        LogManager::PrintByChar("你赢了！\n");
        LogManager::PrintByChar("你获得了敌方的宝可梦！\n");
        auto enemyPoke = _enemyFightPoke->ModelPtr;
        enemyPoke->SetCamp(CampType::Friend);
        PokeManager::GetInstance().AddPoke(enemyPoke->GetElement(), enemyPoke);
    }
}

void FightManager::StartFightForLevel(int levelNumber)
{
    auto level = LevelManager::GetInstance().GetLevel(levelNumber);
    if (level)
    {
        // Show level intro dialogue
        if (levelNumber == 1) DialogueManager::GetInstance().ShowDialogue("level_1_intro");
        else if (levelNumber == 2) DialogueManager::GetInstance().ShowDialogue("level_2_intro");
        else if (levelNumber == 3) DialogueManager::GetInstance().ShowDialogue("level_3_intro");
        else if (levelNumber == 4) DialogueManager::GetInstance().ShowDialogue("level_4_intro");
        else if (levelNumber == 5) DialogueManager::GetInstance().ShowDialogue("level_5_intro");
        else if (levelNumber == 6) DialogueManager::GetInstance().ShowDialogue("boss_intro");

        auto enemyPoke = PokeManager::GetInstance().CreatePoke(level->enemyType, CampType::Enemy);
        SetEnemyFightPoke(enemyPoke);
        StartFight();
    }
    else
    {
        LogManager::PrintByChar("无效的关卡！\n", LogColor::Red);
    }
}

// 显示战斗双方信息
void FightManager::ShowFightInfo() const
{
    LogManager::PrintByChar("现在战斗双方信息如下：\n");
    LogManager::PrintByChar("你的宝可梦：\n");
    GetPlayerFightPoke()->ViewPtr->ShowPokeInfo();
    LogManager::PrintByChar("敌人的宝可梦：\n");
    GetEnemyFightPoke()->ViewPtr->ShowPokeInfo();
}

// 显示战斗开始信息
void FightManager::ShowFightStart() const
{
    LogManager::PrintByChar("你遭遇了敌人！进入战斗！\n");
}

void FightManager::EnterBlankRound()
{
    _fightStateMachine->SwitchState(FightRoundType::Default);
}
