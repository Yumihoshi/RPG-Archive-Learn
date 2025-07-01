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
#include "../MVC/Models/User/UserModel.h" // 包含 UserModel 头文件


class UserManager : public Singleton<UserManager>
{
public:
    // 注册用户
    void RegisterUser();

    // 用户登录
    bool LoginUser();

    // 用户登录循环
    void StartLoop();

    // 新增访问方法
    void SetCurrentUser(const std::shared_ptr<UserModel>& user) { _curUser = user; }
    [[nodiscard]] std::shared_ptr<UserModel> GetCurrentUser() const { return _curUser; }

private:
    std::shared_ptr<UserModel> _curUser;
    UserManager() = default;
    friend class Singleton<UserManager>;
};



#endif //RPG_ARCHIVE_LEARN_USERMANAGER_H
