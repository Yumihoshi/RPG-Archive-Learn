/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午2:54
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_PLAYERFIGHTSTATE_H
#define RPG_ARCHIVE_LEARN_PLAYERFIGHTSTATE_H


#include "../Fsm/BaseState.h"


class PlayerFightState : public BaseState
{
public:
    void OnEnter() override;
    void Handle() override;
    void OnExit() override;
};


#endif //RPG_ARCHIVE_LEARN_PLAYERFIGHTSTATE_H
