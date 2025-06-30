/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午8:29
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_USERMANAGER_H
#define RPG_ARCHIVE_LEARN_USERMANAGER_H


#include "../Base/Singleton.h"


class UserManager : public Singleton<UserManager>
{
public:
    // 注册用户
    void RegisterUser();
    // 用户登录
    bool LoginUser();
private:
    UserManager() = default;
    friend class Singleton<UserManager>;
};


#endif //RPG_ARCHIVE_LEARN_USERMANAGER_H
