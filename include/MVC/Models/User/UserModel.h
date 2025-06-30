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
    const std::string USER_FILE = "../data/users.dat";
public:
    // 构造函数
    UserModel();

    explicit UserModel(std::string username, std::string password,
                       UserType type = UserType::NormalPlayer);

    // Getter
    [[nodiscard]] unsigned int GetId() const;

    [[nodiscard]] std::string GetUsername() const;

    [[nodiscard]] std::string GetPassword() const;

    [[nodiscard]] std::string GetEncryptedPassword() const;

    [[nodiscard]] UserType GetUserType() const;

    // Setter
    void SetUsername(const std::string &username);

    void SetPassword(const std::string &password);

    void SetUserType(UserType type);

    // 简单移位加密
    static std::string Encrypt(const std::string &password);

    // 将用户数据保存到文件
    static void SaveUsersToFile(const std::vector<UserModel> &users,
                                const std::string &filePath);

    // 从文件加载用户数据
    static std::vector<UserModel>
    LoadUsersFromFile(const std::string &filePath);

private:
    unsigned int _id;           // id
    std::string _username;      // 用户名
    std::string _password;      // 密码
    UserType _userType;         // 用户类型
    // TODO: 三个存档槽，完善持久化存储
    // 存档结构体
    struct UserArchive {
        std::string saveDate;
        std::vector<unsigned int> pokeIds; // 通过ID关联宝可梦
        std::map<unsigned int, std::string> pokeStates; // 宝可梦状态，包含装备等信息
    };

    private:
        std::array<UserArchive, 3> _archives; // 3个存档槽位
        static const std::string ARCHIVE_FILE_PREFIX;

    public:
        void SaveArchive(int slot);
        void LoadArchive(int slot);
        void DeleteArchive(int slot);
        void ShowArchiveInfo() const;
};


#endif //RPG_ARCHIVE_LEARN_USERMODEL_H
