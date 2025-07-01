#include "../../include/Managers/PokeManager.h"

PokeManager::PokeManager()
{
    _gen = std::mt19937(_rd());
    _pokeNameMap[ElementType::Fire] = {"小火龙", "烈焰马", "暖暖猪", "火狐狸"};
    _pokeNameMap[ElementType::Ice] = {"迷你冰", "雪童子", "冰伊布", "喷嚏熊"};
    _pokeNameMap[ElementType::Grass] = {"草苗龟", "樱花宝", "青藤蛇",
                                        "坐骑山羊"};
    _pokeNameMap[ElementType::Fly] = {"大比鸟", "飞天螳螂", "长翅鸥", "彩粉蝶"};
    _pokeNameMap[ElementType::Ghost] = {"耿鬼", "魔灵珊瑚", "灵幽马",
                                        "黑夜魔灵"};
}

/// <summary>
/// 添加宝可梦到对应元素类型的容器中
/// </summary>
/// <param name="elementType">宝可梦元素类型</param>
/// <param name="model">宝可梦模型指针</param>
void PokeManager::AddPoke(ElementType elementType,
                          const std::shared_ptr<BasePokeModel> &model)
{
    // 检查元素类型是否已存在于map中
    if (_pokeMap.find(elementType) == _pokeMap.end())
    {
        // 如果不存在，创建一个新的vector
        _pokeMap[elementType] = std::vector<std::shared_ptr<BasePokeModel>>();
    }

    // 将宝可梦添加到对应元素类型的vector中
    _pokeMap[elementType].push_back(model);
}

/// <summary>
/// 获取指定元素类型的所有宝可梦
/// </summary>
/// <param name="elementType">元素类型</param>
/// <returns>宝可梦指针的vector</returns>
std::vector<std::shared_ptr<BasePokeModel>> &
PokeManager::GetPokesByElement(ElementType elementType)
{
    if (_pokeMap.find(elementType) != _pokeMap.end())
    {
        return _pokeMap[elementType];
    }
    _pokeMap[elementType] = std::vector<std::shared_ptr<BasePokeModel>>();
    return _pokeMap[elementType]; // 返回空vector
}

/// <summary>
/// 获取所有宝可梦
/// </summary>
/// <returns>包含所有宝可梦的map</returns>
std::map<ElementType, std::vector<std::shared_ptr<BasePokeModel>>> &
PokeManager::GetAllPokes()
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
bool
PokeManager::RemoveSpecificPoke(const std::shared_ptr<BasePokeModel> &model)
{
    for (auto &pair: _pokeMap)
    {
        auto &pokeVector = pair.second;
        auto it = find(pokeVector.begin(), pokeVector.end(), model);
        if (it != pokeVector.end())
        {
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

bool PokeManager::UpdatePokeAttributes(
        const std::shared_ptr<BasePokeModel> &model,
        const std::function<void(
                std::shared_ptr<BasePokeModel>)> &updateFunction)
{
    // 遍历所有元素类型容器
    for (auto &[element, pokeList]: _pokeMap)
    {
        // 在vector中查找目标宝可梦
        auto it = find(pokeList.begin(), pokeList.end(), model);

        if (it != pokeList.end())
        {
            // 找到宝可梦，执行修改操作
            updateFunction(*it);
            return true;
        }
    }
    return false; // 未找到宝可梦
}

bool PokeManager::UpdatePokeElementType(
        const std::shared_ptr<BasePokeModel> &model,
        ElementType newElementType)
{
    bool found = false;

    // 遍历所有容器寻找宝可梦
    for (auto &[element, pokeList]: _pokeMap)
    {
        auto it = find(pokeList.begin(), pokeList.end(), model);

        if (it != pokeList.end())
        {
            // 从当前容器删除
            pokeList.erase(it);
            found = true;
            break; // 找到后立即跳出循环
        }
    }

    if (found)
    {
        // 添加新容器（自动创建类型容器）
        _pokeMap[newElementType].push_back(model);

        // 可选：更新宝可梦对象的内部元素类型属性
        // model->SetElementType(newElementType);
        return true;
    }
    return false; // 未找到宝可梦
}

/// <summary>
/// 根据名称获取宝可梦
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
std::shared_ptr<BasePokeModel>
PokeManager::GetPokeByName(const std::string &name)
{
    for (auto &[element, pokeList]: _pokeMap)
    {
        for (auto &poke: pokeList)
        {
            if (poke->GetName() == name)
            {
                return poke;
            }
        }
    }
    return nullptr;
}

/// <summary>
/// 根据阵营获取宝可梦
/// </summary>
/// <param name="campType"></param>
/// <returns></returns>
std::shared_ptr<BasePokeModel> PokeManager::GetPokeByCamp(CampType campType)
{
    for (auto &[element, pokeList]: _pokeMap)
    {
        for (auto &poke: pokeList)
        {
            if (poke->GetCamp() == campType)
            {
                return poke;
            }
        }
    }
    return nullptr;
}

// 随机获取宝可梦名字
std::string PokeManager::GetPokeDefaultNameByElement(ElementType elementType)
{
    std::uniform_int_distribution<size_t> dist(0,
                                               _pokeNameMap[elementType].size() -
                                               1);
    return _pokeNameMap[elementType][dist(_gen)];
}

unsigned int PokeManager::GetPokeMaxId() const
{
    return _pokeMaxId;
}

void PokeManager::SetPokeMaxId(unsigned int id)
{
    _pokeMaxId = id;
}

#include "../../include/MVC/Models/Poke/FirePokeModel.h"
#include "../../include/MVC/Models/Poke/GrassPokeModel.h"
#include "../../include/MVC/Models/Poke/IcePokeModel.h"
#include "../../include/MVC/Models/Poke/FlyPokeModel.h"
#include "../../include/MVC/Models/Poke/GhostPokeModel.h"
#include "../../include/MVC/Models/Poke/BossPokeModel.h"

void PokeManager::Init()
{
    // Do nothing
}

std::shared_ptr<BasePokeModel> PokeManager::CreatePoke(ElementType elementType, CampType campType)
{
    std::shared_ptr<BasePokeModel> poke = nullptr;
    switch (elementType)
    {
        case ElementType::Fire:
            poke = std::make_shared<FirePokeModel>(GetPokeDefaultNameByElement(elementType), campType);
            break;
        case ElementType::Grass:
            poke = std::make_shared<GrassPokeModel>(GetPokeDefaultNameByElement(elementType), campType);
            break;
        case ElementType::Ice:
            poke = std::make_shared<IcePokeModel>(GetPokeDefaultNameByElement(elementType), campType);
            break;
        case ElementType::Fly:
            poke = std::make_shared<FlyPokeModel>(GetPokeDefaultNameByElement(elementType), campType);
            break;
        case ElementType::Ghost:
            poke = std::make_shared<GhostPokeModel>(GetPokeDefaultNameByElement(elementType), campType);
            break;
        case ElementType::None:
            poke = std::make_shared<BossPokeModel>("仙后", campType);
            break;
        default:
            break;
    }
    return poke;
}

// 根据ID获取宝可梦
std::shared_ptr<BasePokeModel> PokeManager::GetPokeById(unsigned int id)
{
    for (const auto &[element, pokeList]: _pokeMap)
    {
        for (const auto &poke: pokeList)
        {
            if (poke->GetId() == id)
                return poke;
        }
    }
    return nullptr;
}
