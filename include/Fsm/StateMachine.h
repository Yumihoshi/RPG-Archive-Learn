/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午2:23
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_STATEMACHINE_H
#define RPG_ARCHIVE_LEARN_STATEMACHINE_H

#include <memory>
#include "BaseState.h"

class StateMachine
{
public:
    void SwitchState(std::unique_ptr<BaseState> newState)
    {
        if (_curState)
            _curState->OnExit();
        _curState = std::move(newState);
        if (_curState)
        {
            _curState->OnEnter();
            _curState->Handle();
        }
    }
private:
    // 当前状态
    std::unique_ptr<BaseState> _curState;
};

#endif //RPG_ARCHIVE_LEARN_STATEMACHINE_H
