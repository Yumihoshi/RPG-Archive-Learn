#include <algorithm>
#include "PokemonModel.h"
#include "LogManager.h"
using namespace std;

PokemonModel::PokemonModel(string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
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
void PokemonModel::Heal(int amount)
{
    if (amount <= 0) return;
    _curHp = clamp(_curHp + amount, 0, _maxHp);
}

/// <summary>
/// 扣血
/// </summary>
/// <param name="amount"></param>
void PokemonModel::TakeDamage(int amount)
{
    if (amount <= 0) return;
    _curHp = clamp(_curHp - amount, 0, _maxHp);
}

/// <summary>
/// 回复魔法值
/// </summary>
/// <param name="amount"></param>
void PokemonModel::AddMp(int amount)
{
    if (amount <= 0) return;
    _curMp = clamp(_curMp + amount, 0, _maxMp);
}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void PokemonModel::ReduceMp(int amount)
{
    if (amount <= 0) return;
    _curMp = clamp(_curMp - amount, 0, _maxMp);
}

/// <summary>
/// 增加经验值，会自动处理升级
/// </summary>
/// <param name="amount"></param>
void PokemonModel::AddExp(int amount)
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
    LevelUp(levelUp);
}

/// <summary>
/// 升级
/// </summary>
/// <param name="levelCount">升级等级数</param>
void PokemonModel::LevelUp(int levelCount)
{
    if (levelCount <= 0) return;
    _curLevel = clamp(_curLevel + levelCount, 1, _maxLevel);
}
