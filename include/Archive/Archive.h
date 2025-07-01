/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/1 下午2:10
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_ARCHIVE_H
#define RPG_ARCHIVE_LEARN_ARCHIVE_H


class Archive
{
private:
    unsigned int _id;       // 存档id
private:
    // 检查id是否有效
    [[nodiscard]] bool CheckIdValid() const;
};


#endif //RPG_ARCHIVE_LEARN_ARCHIVE_H
