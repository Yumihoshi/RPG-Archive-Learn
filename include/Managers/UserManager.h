/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/27 下午2:20
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_USERMANAGER_H
#define RPG_ARCHIVE_LEARN_USERMANAGER_H

#include "../Base/Singleton.h"

class UserManager : public Singleton<UserManager>
{
public:
    const std::string USER_FILE = "../data/users.dat";
    // 用户注册
    void RegisterUser();
    // 用户登录
    bool LoginUser();

private:
    // 简单移位加密（实际项目应使用bcrypt等强哈希）
    std::string Encrypt(const std::string& password);

    // 检查用户名是否已存在
    bool IsUsernameAlreadyExist(const std::string& username);

    // 获取密码输入（显示*号）
    std::string GetPassword(const char* prompt);

    friend class Singleton<UserManager>;
    UserManager();
};


#endif //RPG_ARCHIVE_LEARN_USERMANAGER_H
