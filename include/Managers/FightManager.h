/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午2:05
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_FIGHTMANAGER_H
#define RPG_ARCHIVE_LEARN_FIGHTMANAGER_H

#include <memory>
#include <variant>
#include "../MVC/Controllers/BasePokeController.h"
#include "../Base/Singleton.h"
#include "../Fsm/StateMachine.h"
#include "../Common/Types.h"
#include "../Fight/PlayerFightState.h"

class FightManager : public Singleton<FightManager>
{
public:
    // 初始化
    void Init();

    // 开始战斗
    void StartFight();

    // 进入玩家战斗回合
    void EnterPlayerRound();

    // 进入敌人战斗回合
    void EnterEnemyRound();

    // 进入空白默认战斗回合
    void EnterBlankRound();

    // 属性Getter
    [[nodiscard]] std::shared_ptr<BasePokeController>
    GetPlayerFightPoke() const;
    [[nodiscard]] std::shared_ptr<BasePokeController>
    GetEnemyFightPoke() const;

    // 属性Setter
    void SetPlayerFightPoke(const std::shared_ptr<BasePokeModel>& playerModel);
    void SetEnemyFightPoke(const std::shared_ptr<BasePokeModel>& enemyModel);

private:
    std::shared_ptr<BasePokeController> _playerFightPoke;        // 玩家出战宝可梦
    std::shared_ptr<BasePokeController> _enemyFightPoke;         // 敌人出战宝可梦

    std::unique_ptr<StateMachine<FightRoundType>> _fightStateMachine;        // 战斗状态机
private:
    // 显示战斗双方信息
    void ShowFightInfo() const;

    // 显示进入战斗
    void ShowFightStart() const;

    // 单例相关
    FightManager();

    friend class Singleton<FightManager>;
};


#endif //RPG_ARCHIVE_LEARN_FIGHTMANAGER_H
