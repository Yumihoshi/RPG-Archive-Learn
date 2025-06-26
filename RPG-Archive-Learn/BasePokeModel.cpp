#include <algorithm>
#include <string>
#include <random>
#include "BasePokeModel.h"
#include "LogManager.h"

BasePokeModel::BasePokeModel(std::string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
    CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate, int damage)
{
    _name = name;
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
    LogManager::GetInstance().PrintByChar(_name + "回血" + std::to_string(amount) + "，现在血量为：" + std::to_string(_curHp) + "\n");
}

/// <summary>
/// 扣血
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::TakeDamage(int amount)
{
    if (amount <= 0) return;
    auto& logger = LogManager::GetInstance();
    // 闪避
    if (CheckFlee())
    {
        logger.PrintByChar(_name + "触发了");
        logger.PrintByChar("闪避", LogColor::Yellow);
        logger.PrintByChar("！\n");
        return;
    }
    else
    {
        _curHp = std::clamp(_curHp - amount, 0, _maxHp);
        LogManager::GetInstance().PrintByChar(_name + "扣血" + std::to_string(amount) + "，现在血量为：" + std::to_string(_curHp) + "\n");
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
    LogManager::GetInstance().PrintByChar(_name + "回魔" + std::to_string(amount) + "，现在魔法值为：" + std::to_string(_curMp) + "\n");
}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::ReduceMp(int amount)
{
    if (amount <= 0) return;
    _curMp = std::clamp(_curMp - amount, 0, _maxMp);
    LogManager::GetInstance().PrintByChar(_name + "扣魔" + std::to_string(amount) + "，现在魔法值为：" + std::to_string(_curMp) + "\n");
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
    LogManager::GetInstance().PrintByChar(_name + "经验值增加" + std::to_string(amount) + "，现在经验值为：" + std::to_string(_curExp) + "\n");
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
    LogManager::GetInstance().PrintByChar(_name + "升级啦，现在等级为：" + std::to_string(_curLevel) + "\n");
}

std::string BasePokeModel::GetName()
{
    return _name;
}

int BasePokeModel::GetCurHp()
{
    return _curHp;
}

int BasePokeModel::GetMaxHp()
{
    return _maxHp;
}

int BasePokeModel::GetCurMp()
{
    return _curMp;
}

int BasePokeModel::GetMaxMp()
{
    return _maxMp;
}

float BasePokeModel::GetFleeRate()
{
    return _fleeRate;
}

float BasePokeModel::GetCritRate()
{
    return _critRate;
}

/// <summary>
/// 检验是否触发闪避
/// </summary>
/// <returns></returns>
bool BasePokeModel::CheckFlee() {
    // 生成0.0~1.0的随机浮点数
    static std::random_device _rd;
    static std::mt19937 gen(_rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    double randValue = dist(gen);
    return randValue < _fleeRate; // 若随机数小于闪避率，返回true
}

int BasePokeModel::GetCurExp()
{
    return _curExp;
}

int BasePokeModel::GetMaxExp()
{
    return _maxExp;
}
int BasePokeModel::GetCurLevel()
{
    return _curLevel;
}

int BasePokeModel::GetMaxLevel()
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
    _decoration = decoration;
    _decoration->Owner = std::make_shared<BasePokeModel>(*this);
    _damage += _decoration->AttackBonus;
    _maxMp += _decoration->MaxMpBonus;
    _critRate += _decoration->CritRateBonus;
}

// 装备防具
void BasePokeModel::Equip(std::shared_ptr<Armor> armor)
{
    _armor = armor;
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

int BasePokeModel::GetDamage()
{
    return _damage;
}
