/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午7:14
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_USERVIEW_H
#define RPG_ARCHIVE_LEARN_USERVIEW_H

#include <string>

class UserView
{
public:
    // 显示登录菜单
    void ShowLoginMenu();
    // 显示注册成功信息
    void ShowRegistrationSuccess();
    // 显示登录成功信息
    void ShowLoginSuccess(const std::string& username);
    // 显示输入错误信息
    void ShowInputError(const std::string& message);
    // 获取用户名输入
    std::string GetUsernameInput();
    // 获取密码输入
    std::string GetPasswordInput();
};


#endif //RPG_ARCHIVE_LEARN_USERVIEW_H
