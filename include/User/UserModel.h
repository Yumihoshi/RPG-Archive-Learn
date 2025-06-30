/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/6/30 下午1:41
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_USERMODEL_H
#define RPG_ARCHIVE_LEARN_USERMODEL_H


#include <string>
#include <vector>

class UserModel
{
private:
    unsigned int _id;           // id
    std::string _username;      // 用户名
    std::string _password;      // 密码
    // TODO: 三个存档槽，完善持久化存储
};


#endif //RPG_ARCHIVE_LEARN_USERMODEL_H
