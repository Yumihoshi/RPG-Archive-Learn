#pragma once

#include <iostream>

using namespace std;

/// <summary>
/// 元素属性枚举
/// </summary>
enum class ElementType
{
    /// <summary>
    /// 火
    /// </summary>
    Fire = 1,

    /// <summary>
    /// 冰
    /// </summary>
    Ice,

    /// <summary>
    /// 自然
    /// </summary>
    Nature
};

/// <summary>
/// 阵营枚举
/// </summary>
enum class CampType
{
    Friend,
    Enemy
};

class BasePokeModel
{
public:
    BasePokeModel(string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate);

    /// <summary>
    /// 回血
    /// </summary>
    /// <param name="amount"></param>
    void Heal(int amount);

    /// <summary>
    /// 扣血
    /// </summary>
    /// <param name="amount"></param>
    virtual void TakeDamage(int amount);

    /// <summary>
    /// 回复魔法值
    /// </summary>
    /// <param name="amount"></param>
    void AddMp(int amount);

    /// <summary>
    /// 减少魔法值
    /// </summary>
    /// <param name="amount"></param>
    void ReduceMp(int amount);

    /// <summary>
    /// 增加经验值
    /// </summary>
    /// <param name="amount"></param>
    void AddExp(int amount);

    /// <summary>
    /// 升级
    /// </summary>
    /// <param name="levelCount">升级等级数</param>
    void LevelUp(int levelCount = 1);

    string GetName();
    int GetCurHp();
    int GetMaxHp();
    int GetCurMp();
    int GetMaxMp();
    float GetFleeRate();
    float GetCritRate();

protected:
    string _name;      // 宝可梦名
    ElementType _element;     // 职业枚举类型
    CampType _camp;     // 阵营枚举类型

    int _curHp;     // 当前血量
    int _maxHp;     // 最大血量

    int _curMp;     // 当前魔法值
    int _maxMp;     // 最大魔法值
    int _turnRecoverMp;     // 每回合回复魔法值

    int _curExp;        // 当前经验值
    int _maxExp;        // 最大经验值

    int _curLevel;      // 当前等级
    int _maxLevel;      // 最大等级

    float _fleeRate;        // 闪避率
    float _critRate;        // 暴击率

    bool CheckFlee();
};
