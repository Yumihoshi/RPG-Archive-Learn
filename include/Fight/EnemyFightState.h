/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午4:36
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_ENEMYFIGHTSTATE_H
#define RPG_ARCHIVE_LEARN_ENEMYFIGHTSTATE_H


#include "../Fsm/BaseState.h"


class EnemyFightState : public BaseState
{
public:
    void OnEnter() override;
    void Handle() override;
    void OnExit() override;
};


#endif //RPG_ARCHIVE_LEARN_ENEMYFIGHTSTATE_H
