#pragma once
#include <iostream>

using namespace std;

enum class ProfessionType
{
    /// <summary>
    /// 战士
    /// </summary>
    Warrior = 1,

    /// <summary>
    /// 元素法师
    /// </summary>
    EleMage,

    /// <summary>
    /// 弓箭手
    /// </summary>
    Archer
};

enum class CampType
{
    Friend,
    Enemy
};

class CharacterModel
{
public:
    CharacterModel(string name, ProfessionType profession, int maxHp, int maxMp, int turnRecoverMp);

    /// <summary>
    /// 回血
    /// </summary>
    /// <param name="amount"></param>
    void Heal(int amount);

    /// <summary>
    /// 扣血
    /// </summary>
    /// <param name="amount"></param>
    void TakeDamage(int amount);

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

private:
    string _name;      // 宝可梦名
    ProfessionType _profession;     // 职业枚举类型
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
};
