#include "PokeManager.h"

PokeManager::PokeManager() = default;

/// <summary>
/// 添加宝可梦到对应元素类型的容器中
/// </summary>
/// <param name="elementType">宝可梦元素类型</param>
/// <param name="model">宝可梦模型指针</param>
void PokeManager::AddPoke(ElementType elementType, shared_ptr<BasePokeModel> model)
{
    // 检查元素类型是否已存在于map中
    if (_pokeMap.find(elementType) == _pokeMap.end())
    {
        // 如果不存在，创建一个新的vector
        _pokeMap[elementType] = vector<shared_ptr<BasePokeModel>>();
    }

    // 将宝可梦添加到对应元素类型的vector中
    _pokeMap[elementType].push_back(model);
}

/// <summary>
/// 获取指定元素类型的所有宝可梦
/// </summary>
/// <param name="elementType">元素类型</param>
/// <returns>宝可梦指针的vector</returns>
vector<shared_ptr<BasePokeModel>> PokeManager::GetPokesByElement(ElementType elementType)
{
    if (_pokeMap.find(elementType) != _pokeMap.end())
    {
        return _pokeMap[elementType];
    }
    return vector<shared_ptr<BasePokeModel>>(); // 返回空vector
}

/// <summary>
/// 获取所有宝可梦
/// </summary>
/// <returns>包含所有宝可梦的map</returns>
map<ElementType, vector<shared_ptr<BasePokeModel>>> PokeManager::GetAllPokes()
{
    return _pokeMap;
}

/// <summary>
/// 删除宝可梦
/// </summary>
/// <param name="elementType"></param>
/// <returns></returns>
bool PokeManager::RemovePokesByElement(ElementType elementType)
{
    return _pokeMap.erase(elementType) > 0;
}

/// <summary>
/// 删除特定的宝可梦
/// </summary>
/// <param name="model">要删除的宝可梦指针</param>
/// <returns>是否找到并删除</returns>
bool PokeManager::RemoveSpecificPoke(shared_ptr<BasePokeModel> model)
{
    for (auto& pair : _pokeMap) {
        auto& pokeVector = pair.second;
        auto it = find(pokeVector.begin(), pokeVector.end(), model);
        if (it != pokeVector.end()) {
            pokeVector.erase(it);
            return true;
        }
    }
    return false;
}

/// <summary>
/// 清空所有宝可梦
/// </summary>
void PokeManager::ClearAllPokes()
{
    _pokeMap.clear();
}
