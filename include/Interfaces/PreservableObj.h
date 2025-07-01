/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/1 下午2:18
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARCHIVE_LEARN_PRESERVABLEOBJ_H
#define RPG_ARCHIVE_LEARN_PRESERVABLEOBJ_H


class PreservableObj
{
    virtual void Save() = 0;
    virtual void Load() = 0;
};


#endif //RPG_ARCHIVE_LEARN_PRESERVABLEOBJ_H
