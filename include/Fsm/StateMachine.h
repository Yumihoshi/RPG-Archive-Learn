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
#include <map>
#include "BaseState.h"

template<typename StateEnum>
class StateMachine
{
public:
    void SwitchState(StateEnum newState)
    {
        if (_curState)
            _curState->OnExit();
        _curState = _states[newState];
        if (_curState == nullptr)
            std::cout << "StateMachine: State not found" << std::endl;
        _curState->OnEnter();
        _curState->Handle();
    }

    void AddState(StateEnum state, std::unique_ptr<BaseState> statePtr)
    {
        _states[state] = std::move(statePtr);
    }

    void RemoveState(StateEnum state)
    {
        _states.erase(state);
    }
private:
    // 当前状态
    std::map<StateEnum, std::shared_ptr<BaseState>> _states;
    std::shared_ptr<BaseState> _curState;
};

#endif //RPG_ARCHIVE_LEARN_STATEMACHINE_H
