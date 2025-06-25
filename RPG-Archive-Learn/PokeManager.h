#pragma once
#include <map>
#include <vector>
#include <functional>
#include "Singleton.h"
#include "Types.h"
#include "BasePokeModel.h"

using namespace std;

class PokeManager :public Singleton<PokeManager>
{
public:
    // ##########增加##########

    /// <summary>
    /// 添加宝可梦到对应元素类型的容器中
    /// </summary>
    /// <param name="elementType">宝可梦元素类型</param>
    /// <param name="model">宝可梦模型指针</param>
    void AddPoke(ElementType elementType, shared_ptr<BasePokeModel> model);

    // ##########查找##########

    /// <summary>
    /// 获取指定元素类型的所有宝可梦
    /// </summary>
    /// <param name="elementType">元素类型</param>
    /// <returns>宝可梦指针的vector</returns>
    vector<shared_ptr<BasePokeModel>>& GetPokesByElement(ElementType elementType);

    /// <summary>
    /// 获取所有宝可梦
    /// </summary>
    /// <returns>包含所有宝可梦的map</returns>
    map<ElementType, vector<shared_ptr<BasePokeModel>>>& GetAllPokes();

    /// <summary>
    /// 根据名称获取宝可梦
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    shared_ptr<BasePokeModel> GetPokeByName(string name);

    /// <summary>
    /// 根据阵营获取宝可梦
    /// </summary>
    /// <param name="campType"></param>
    /// <returns></returns>
    shared_ptr<BasePokeModel> GetPokeByCamp(CampType campType);

    // ##########删除##########

    /// <summary>
    /// 删除宝可梦
    /// </summary>
    /// <param name="elementType"></param>
    /// <returns></returns>
    bool RemovePokesByElement(ElementType elementType);

    /// <summary>
    /// 删除特定的宝可梦
    /// </summary>
    /// <param name="model">要删除的宝可梦指针</param>
    /// <returns>是否找到并删除</returns>
    bool RemoveSpecificPoke(shared_ptr<BasePokeModel> model);

    /// <summary>
    /// 清空所有宝可梦
    /// </summary>
    void ClearAllPokes();

    // ##########修改##########

    /// <summary>
    /// 修改宝可梦属性（不改变元素类型）
    /// </summary>
    /// <param name="model">要修改的宝可梦指针</param>
    /// <param name="updateFunction">自定义更新函数</param>
    /// <returns>是否成功找到并更新</returns>
    bool UpdatePokeAttributes(
        shared_ptr<BasePokeModel> model,
        function<void(shared_ptr<BasePokeModel>)> updateFunction
    );

    /// <summary>
    /// 修改宝可梦元素类型
    /// </summary>
    /// <param name="model">要修改的宝可梦指针</param>
    /// <param name="newElementType">新的元素类型</param>
    /// <returns>是否成功更新</returns>
    bool UpdatePokeElementType(
        shared_ptr<BasePokeModel> model,
        ElementType newElementType
    );

private:
    friend class Singleton<PokeManager>;
    map < ElementType, vector<shared_ptr<BasePokeModel> >> _pokeMap;
    PokeManager();
};