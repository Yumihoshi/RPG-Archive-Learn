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
    // TODO: muliao实现
    if (amount > 0) 
    {
        int a = _curHp + amount;
        if (a <= _maxHp)
        {
            _curHp = a;
        }
    }
    else
    {
        LogManager::GetInstance().PrintByChar("Heal方法回血不能为负数\n");
    }
}

/// <summary>
/// 扣血
/// </summary>
/// <param name="amount"></param>
void PokemonModel::TakeDamage(int amount)
{
    // TODO: muliao实现
    if(amount> 0)
    {
        int b = _curHp - amount;
       if (b >= 0 )
       {
           _curHp = b;
       }
    }
    else
    {
        LogManager::GetInstance().PrintByChar("TakeDamage方法扣血不能为负数\n");
    }
}

/// <summary>
/// 回复魔法值
/// </summary>
/// <param name="amount"></param>
void PokemonModel::AddMp(int amount)
{
    // TODO: muliao实现
    if (amount > 0)
    {
        int c = _curMp + amount;
        if (c <= _curMp)
        {
            _curMp = c;
        }
    }
    else
    {
        LogManager::GetInstance().PrintByChar("AddMp方法回魔不能为负数\n");
    }
}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void PokemonModel::ReduceMp(int amount)
{
    // TODO: muliao实现
    if (amount > 0)
    {
        int d = _curMp - amount;
        if (d >= 0)
        {
            _curMp = d;
        }
    }
    else
    {
        LogManager::GetInstance().PrintByChar("ReduceMp方法扣魔不能为负数\n");
    }
}

/// <summary>
/// 增加经验值
/// </summary>
/// <param name="amount"></param>
void PokemonModel::AddExp(int amount)
{
    // TODO: muliao实现

}

/// <summary>
/// 升级
/// </summary>
/// <param name="levelCount">升级等级数</param>
void PokemonModel::LevelUp(int levelCount)
{
    // TODO: muliao实现

}
