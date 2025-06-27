#include <algorithm>
#include <string>
#include <random>
#include <utility>
#include "../../../include/MVC/Models/BasePokeModel.h"
#include "../../../include/Managers/LogManager.h"
#include "../../../include/Common/Common.h"

BasePokeModel::BasePokeModel()
{
    _name = "";
    _element = ElementType::None;
    _maxHp = 100;
    _maxMp = 50;
    _maxExp = 100;
    _maxLevel = 10;
    _critRate = 0.15f;
    _fleeRate = 0.1f;
    _damage = 10;
    _turnRecoverMp = 5;
    _camp = CampType::None;
    _curHp = _maxHp;
    _curMp = _maxMp;
    _curExp = 0;
    _curLevel = 1;
}

BasePokeModel::BasePokeModel(std::string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
    CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate, int damage)
{
    _name = std::move(name);
    _element = ele;
    _maxHp = maxHp;
    _maxMp = maxMp;
    _maxExp = maxExp;
    _maxLevel = maxLevel;
    _turnRecoverMp = turnRecoverMp;
    _camp = camp;
    _critRate = critRate;
    _fleeRate = fleeRate;
    _damage = damage;
    // 当前状态初始化
    _curHp = maxHp;
    _curMp = maxMp;
    _curLevel = 1;
    _curExp = 0;
}

/// <summary>
/// 回血
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::Heal(int amount)
{
    if (amount <= 0) return;
    _curHp = std::clamp(_curHp + amount, 0, _maxHp);
    LogManager::PrintByChar(_name + "回血" + std::to_string(amount) + "，现在血量为：" + std::to_string(_curHp) + "\n");
}

/// <summary>
/// 扣血
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::TakeDamage(int amount)
{
    if (!IsAlive()) return;
    if (amount <= 0) return;
    // 闪避
    if (CheckFlee())
    {
        LogManager::PrintByChar(_name + "触发了");
        LogManager::PrintByChar("闪避", LogColor::Yellow);
        LogManager::PrintByChar("！\n");
        return;
    }
    else
    {
        _curHp = std::clamp(_curHp - amount, 0, _maxHp);
        LogManager::PrintByChar(_name + "扣血" + std::to_string(amount) + "，现在血量为：" + std::to_string(_curHp) + "\n");
        if (!IsAlive())
        {
            LogManager::PrintByChar(_name + "已死亡！\n", LogColor::Red);
        }
    }
}

/// <summary>
/// 回复魔法值
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::AddMp(int amount)
{
    if (amount <= 0) return;
    _curMp = std::clamp(_curMp + amount, 0, _maxMp);
    LogManager::PrintByChar(_name + "回魔" + std::to_string(amount) + "，现在魔法值为：" + std::to_string(_curMp) + "\n");
}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::ReduceMp(int amount)
{
    if (amount <= 0) return;
    _curMp = std::clamp(_curMp - amount, 0, _maxMp);
    LogManager::PrintByChar(_name + "扣魔" + std::to_string(amount) + "，现在魔法值为：" + std::to_string(_curMp) + "\n");
}

/// <summary>
/// 增加经验值，会自动处理升级
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::AddExp(int amount)
{
    if (amount <= 0) return;
    int levelUp = amount / _maxExp;
    int restExp = amount % _maxExp;
    int tempExp = _curExp + restExp;
    if (tempExp >= _maxExp)
    {
        tempExp = 0;
        levelUp++;
    }
    _curExp = tempExp;
    LogManager::PrintByChar(_name + "经验值增加" + std::to_string(amount) + "，现在经验值为：" + std::to_string(_curExp) + "\n");
    LevelUp(levelUp);
}

/// <summary>
/// 升级
/// </summary>
/// <param name="levelCount">升级等级数</param>
void BasePokeModel::LevelUp(int levelCount)
{
    if (levelCount <= 0) return;
    _curLevel = std::clamp(_curLevel + levelCount, 1, _maxLevel);
    LogManager::PrintByChar(_name + "升级啦，现在等级为：" + std::to_string(_curLevel) + "\n");
}

std::string BasePokeModel::GetName()
{
    return _name;
}

int BasePokeModel::GetCurHp() const
{
    return _curHp;
}

int BasePokeModel::GetMaxHp() const
{
    return _maxHp;
}

int BasePokeModel::GetCurMp() const
{
    return _curMp;
}

int BasePokeModel::GetMaxMp() const
{
    return _maxMp;
}

float BasePokeModel::GetFleeRate() const
{
    return _fleeRate;
}

float BasePokeModel::GetCritRate() const
{
    return _critRate;
}

/// <summary>
/// 检验是否触发闪避
/// </summary>
/// <returns></returns>
bool BasePokeModel::CheckFlee() const {
    // 生成0.0~1.0的随机浮点数
    static std::random_device _rd;
    static std::mt19937 gen(_rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    double randValue = dist(gen);
    return randValue < _fleeRate; // 若随机数小于闪避率，返回true
}

int BasePokeModel::GetCurExp() const
{
    return _curExp;
}

int BasePokeModel::GetMaxExp() const
{
    return _maxExp;
}
int BasePokeModel::GetCurLevel() const
{
    return _curLevel;
}

int BasePokeModel::GetMaxLevel() const
{
    return _maxLevel;
}

CampType BasePokeModel::GetCamp()
{
    return _camp;
}

// 装备饰品
void BasePokeModel::Equip(std::shared_ptr<Decoration> decoration)
{
    _decoration = std::move(decoration);
    _decoration->Owner = std::make_shared<BasePokeModel>(*this);
    _damage += _decoration->AttackBonus;
    _maxMp += _decoration->MaxMpBonus;
    _critRate += _decoration->CritRateBonus;
}

// 装备防具
void BasePokeModel::Equip(std::shared_ptr<Armor> armor)
{
    _armor = std::move(armor);
    _armor->Owner = std::make_shared<BasePokeModel>(*this);
    _maxHp += _armor->MaxHpBonus;
    _fleeRate += _armor->FleeRateBonus;
}

// 卸下饰品
void BasePokeModel::Unequip(EquipType equipType)
{
    if (equipType == EquipType::Decoration)
    {
        if (_decoration == nullptr) return;
        _damage -= _decoration->AttackBonus;
        _maxMp -= _decoration->MaxMpBonus;
        _critRate -= _decoration->CritRateBonus;
        _decoration->Owner = nullptr;
        _decoration = nullptr;
    }
    else if (equipType == EquipType::Armor)
    {
        if (_armor == nullptr) return;
        _maxHp -= _armor->MaxHpBonus;
        _fleeRate -= _armor->FleeRateBonus;
        _armor->Owner = nullptr;
        _armor = nullptr;
    }
    else
    {
        throw std::invalid_argument("equipType");
    }
}

int BasePokeModel::GetDamage() const
{
    return _damage;
}

// 属性随机扰动
void BasePokeModel::PerturbAttribute()
{
    _maxHp *= Common::GetRandomFloat(0.9f, 1.1f);
    _maxMp *= Common::GetRandomFloat(0.9f, 1.1f);
    _damage *= Common::GetRandomFloat(0.9f, 1.1f);
    _critRate *= Common::GetRandomFloat(0.9f, 1.1f);
    _fleeRate *= Common::GetRandomFloat(0.9f, 1.1f);
    _turnRecoverMp *= Common::GetRandomFloat(0.9f, 1.1f);
}

void BasePokeModel::ResetCur()
{
    _curHp = _maxHp;
    _curMp = _maxMp;
}

ElementType BasePokeModel::GetElement()
{
    return _element;
}

std::string BasePokeModel::GetStory()
{
    return _story;
}

void BasePokeModel::SetStory(std::string story)
{
    _story = std::move(story);
}

bool BasePokeModel::IsAlive() const
{
    return _curHp > 0;
}

void BasePokeModel::Init()
{
    PerturbAttribute();
    ResetCur();
}

unsigned int BasePokeModel::GetId() const
{
    return _id;
}

void BasePokeModel::SetId(unsigned int id)
{
    _id = id;
}

std::shared_ptr<Decoration> BasePokeModel::GetDecoration() const
{
    return _decoration;
}

std::shared_ptr<Armor> BasePokeModel::GetArmor() const
{
    return _armor;
}
