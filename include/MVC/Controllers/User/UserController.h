/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午7:14
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_USERCONTROLLER_H
#define RPG_ARCHIVE_LEARN_USERCONTROLLER_H


#include <memory>
#include "../../Models/User/UserModel.h"
#include "../../Views/User/UserView.h"

class UserController
{
public:
    explicit UserController(std::shared_ptr<UserModel> model,
                          std::shared_ptr<UserView> view);
    // 处理注册
    bool RegisterUser(std::vector<UserModel>& users);
    // 处理登录
    bool LoginUser(const std::vector<UserModel>& users);

private:
    std::shared_ptr<UserModel> _model;
    std::shared_ptr<UserView> _view;
    static std::string GetPassword(const char *prompt);
};


#endif //RPG_ARCHIVE_LEARN_USERCONTROLLER_H
