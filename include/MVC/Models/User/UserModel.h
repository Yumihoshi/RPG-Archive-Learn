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
#include <map>
#include "../../../Common/Types.h"

class UserModel
{
public:
    static const std::string USER_FILE;
public:
    // 构造函数
    UserModel();

    explicit UserModel(std::string username, std::string password,
                       UserType type = UserType::NormalPlayer);
    UserModel(std::string username, std::string password, UserType type,
                         unsigned int id);

    // Getter
    [[nodiscard]] unsigned int GetId() const;

    [[nodiscard]] std::string GetUsername() const;

    [[nodiscard]] std::string GetEncryptPassword() const;

    [[nodiscard]] std::string GetOriginPassword() const;

    [[nodiscard]] UserType GetUserType() const;

    // Setter
    void SetUsername(const std::string &username);

    void SetPassword(const std::string &password);

    void SetUserType(UserType type);

    // 是否是第一次游玩
    [[nodiscard]] bool IsFirstTime() const { return _isFirstTime; }
    void SetFirstTime(bool isFirstTime) { _isFirstTime = isFirstTime; }

    // 简单移位加密
    static std::string Encrypt(const std::string &password);

    // 简单移位解密
    static std::string Decrypt(const std::string &encryptedPassword);

    // 将用户数据保存到文件
    static void SaveUsersToFile(const std::vector<UserModel> &users,
                                const std::string &filePath);

    // 从文件加载用户数据
    static std::vector<UserModel>
    LoadUsersFromFile(const std::string &filePath);

    // 根据用户ID查找用户
    static std::shared_ptr<UserModel> FindUserById(unsigned int id);

private:
    unsigned int _id;           // id
    std::string _username;      // 用户名
    std::string _password;      // 密码
    UserType _userType;         // 用户类型
    bool _isFirstTime;          // 是否是第一次游玩
    // TODO: 三个存档槽，完善持久化存储

    friend void to_json(json& j, const UserModel& p);
    friend void from_json(const json& j, UserModel& p);
};

inline void to_json(json& j, const UserModel& u) {
    j = json{
        {"_id", u._id},
        {"_username", u._username},
        {"_password", u._password},
        {"_userType", u._userType},
        {"_isFirstTime", u._isFirstTime}
    };
}

inline void from_json(const json& j, UserModel& u) {
    j.at("_id").get_to(u._id);
    j.at("_username").get_to(u._username);
    j.at("_password").get_to(u._password);
    j.at("_userType").get_to(u._userType);
    j.at("_isFirstTime").get_to(u._isFirstTime);
}


#endif //RPG_ARCHIVE_LEARN_USERMODEL_H
