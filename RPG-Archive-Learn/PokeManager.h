#pragma once
#include <map>
#include <vector>
#include "Singleton.h"
#include "Types.h"
#include "BasePokeModel.h"

using namespace std;

class PokeManager :public Singleton<PokeManager>
{
public:
    /// <summary>
    /// 添加宝可梦到对应元素类型的容器中
    /// </summary>
    /// <param name="elementType">宝可梦元素类型</param>
    /// <param name="model">宝可梦模型指针</param>
    void AddPoke(ElementType elementType, shared_ptr<BasePokeModel> model);

    /// <summary>
    /// 获取指定元素类型的所有宝可梦
    /// </summary>
    /// <param name="elementType">元素类型</param>
    /// <returns>宝可梦指针的vector</returns>
    vector<shared_ptr<BasePokeModel>> GetPokesByElement(ElementType elementType);

    /// <summary>
    /// 获取所有宝可梦
    /// </summary>
    /// <returns>包含所有宝可梦的map</returns>
    map<ElementType, vector<shared_ptr<BasePokeModel>>> GetAllPokes();

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

private:
    friend class Singleton<PokeManager>;
    map < ElementType, vector<shared_ptr<BasePokeModel> >> _pokeMap;
    PokeManager();
};