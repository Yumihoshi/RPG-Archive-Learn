/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/1 下午2:10
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_ARCHIVE_H
#define RPG_ARCHIVE_LEARN_ARCHIVE_H


#include <memory>
#include <xlnt/xlnt.hpp>
#include "../Interfaces/PreservableObj.h"
#include "../MVC/Models/User/UserModel.h"
#include "../MVC/Models/Poke/BasePokeModel.h"

class Archive : public PreservableObj
{
public:
    static const std::string ARCHIVE_FILE_PRE_PATH;
public:
    // 构造函数
    explicit Archive(unsigned int id, const std::shared_ptr<UserModel> &user);

    // 存档逻辑
    void Save() override;

    void Load() override;

    // 初始化新用户存档
    static void InitNewUserArchive(const std::shared_ptr<UserModel> &user);

    // Getter
    [[nodiscard]] unsigned int GetId() const
    { return _id; }

    [[nodiscard]] std::shared_ptr<UserModel> GetUser() const
    { return _user; }

    // Setter
    void SetId(unsigned int id)
    {
        if (!CheckIdValid(id))
            throw std::runtime_error("非法存档id，存档id必须在1-3闭区间内！");
        _id = id;
    }

    void SetUser(const std::shared_ptr<UserModel> &user)
    { _user = user; }

private:
    unsigned int _id;       // 存档id
    std::shared_ptr<UserModel> _user;       // 存档用户

private:
    // 检查id是否有效
    static bool CheckIdValid(unsigned int id);

    // 初始化新用户存档文件夹
    static void
    InitNewUserArchiveFolder(const std::shared_ptr<UserModel> &user);
};


#endif //RPG_ARCHIVE_LEARN_ARCHIVE_H
