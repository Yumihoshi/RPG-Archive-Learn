/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午2:20
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_BASESTATE_H
#define RPG_ARCHIVE_LEARN_BASESTATE_H

class BaseState
{
public:
    virtual ~BaseState() = default;
    virtual void OnEnter() = 0;
    virtual void Handle() = 0;
    virtual void OnExit() = 0;
};

#endif //RPG_ARCHIVE_LEARN_BASESTATE_H
