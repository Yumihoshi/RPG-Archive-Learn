#include <algorithm>
#include <string>
#include <random>
#include "BasePokeModel.h"
#include "LogManager.h"

using namespace std;

BasePokeModel::BasePokeModel(string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
    CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate)
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
    _curHp = clamp(_curHp + amount, 0, _maxHp);
    LogManager::GetInstance().PrintByChar(_name + "回血" + to_string(amount) + "，现在血量为：" + to_string(_curHp) + "\n");
}

/// <summary>
/// 扣血
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::TakeDamage(int amount)
{
    if (amount <= 0) return;
    _curHp = clamp(_curHp - amount, 0, _maxHp);
    LogManager::GetInstance().PrintByChar(_name + "扣血" + to_string(amount) + "，现在血量为：" + to_string(_curHp) + "\n");
}

/// <summary>
/// 回复魔法值
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::AddMp(int amount)
{
    if (amount <= 0) return;
    _curMp = clamp(_curMp + amount, 0, _maxMp);
    LogManager::GetInstance().PrintByChar(_name + "回魔" + to_string(amount) + "，现在魔法值为：" + to_string(_curMp) + "\n");
}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void BasePokeModel::ReduceMp(int amount)
{
    if (amount <= 0) return;
    _curMp = clamp(_curMp - amount, 0, _maxMp);
    LogManager::GetInstance().PrintByChar(_name + "扣魔" + to_string(amount) + "，现在魔法值为：" + to_string(_curMp) + "\n");
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
    LogManager::GetInstance().PrintByChar(_name + "经验值增加" + to_string(amount) + "，现在经验值为：" + to_string(_curExp) + "\n");
    LevelUp(levelUp);
}

/// <summary>
/// 升级
/// </summary>
/// <param name="levelCount">升级等级数</param>
void BasePokeModel::LevelUp(int levelCount)
{
    if (levelCount <= 0) return;
    _curLevel = clamp(_curLevel + levelCount, 1, _maxLevel);
    LogManager::GetInstance().PrintByChar(_name + "升级啦，现在等级为：" + to_string(_curLevel) + "\n");
}

string BasePokeModel::GetName()
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
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    double randValue = dist(gen);
    return randValue < _fleeRate; // 若随机数小于闪避率，返回true
}
