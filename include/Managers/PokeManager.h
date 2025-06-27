#pragma once
#include <map>
#include <vector>
#include <functional>
#include <random>
#include "../Base/Singleton.h"
#include "../Common/Types.h"
#include "../MVC/Models/BasePokeModel.h"


class PokeManager :public Singleton<PokeManager>
{
public:
    // ##########增加##########

    // 添加宝可梦到对应元素类型的容器中
    void AddPoke(ElementType elementType, const std::shared_ptr<BasePokeModel>& model);

    // ##########查找##########

    // 根据ID获取宝可梦
    std::shared_ptr<BasePokeModel> GetPokeById(unsigned int id);

    // 获取指定元素类型的所有宝可梦
    std::vector<std::shared_ptr<BasePokeModel>>& GetPokesByElement(ElementType elementType);

    // 获取所有宝可梦
    std::map<ElementType, std::vector<std::shared_ptr<BasePokeModel>>>& GetAllPokes();

    // 根据名称获取宝可梦
    std::shared_ptr<BasePokeModel> GetPokeByName(const std::string& name);

    // 根据阵营获取宝可梦
    std::shared_ptr<BasePokeModel> GetPokeByCamp(CampType campType);

    // ##########删除##########

    // 删除宝可梦
    bool RemovePokesByElement(ElementType elementType);

    // 删除特定的宝可梦
    bool RemoveSpecificPoke(const std::shared_ptr<BasePokeModel>& model);

    // 清空所有宝可梦
    void ClearAllPokes();

    // ##########修改##########

    // 修改宝可梦属性（不改变元素类型）
    bool UpdatePokeAttributes(
        const std::shared_ptr<BasePokeModel>& model,
        const std::function<void(std::shared_ptr<BasePokeModel>)>& updateFunction
    );

    // 修改宝可梦元素类型
    bool UpdatePokeElementType(
        const std::shared_ptr<BasePokeModel>& model,
        ElementType newElementType
    );

    // 随机获取宝可梦名字
    std::string GetPokeDefaultNameByElement(ElementType elementType);

    unsigned int GetPokeMaxId() const;
    void SetPokeMaxId(unsigned int id);

private:
    friend class Singleton<PokeManager>;
    PokeManager();
private:
    // 存储所有宝可梦的容器
    std::map < ElementType, std::vector<std::shared_ptr<BasePokeModel> >> _pokeMap;
    // 存储每个元素类型的默认宝可梦名字
    std::map<ElementType, std::vector<std::string>> _pokeNameMap;

    // 宝可梦id
    unsigned int _pokeMaxId = 0;

    // 随机数生成器
    std::random_device _rd;
    std::mt19937 _gen;
};
