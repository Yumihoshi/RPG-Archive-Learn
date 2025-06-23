#include "CharacterModel.h"
using namespace std;

CharacterModel::CharacterModel(const string& name, ProfessionType profession, int maxHp, int maxMp, int turnRecoverMp)
{
    _name = name;
    _profession = profession;
    _maxHp = maxHp;
    _maxMp = maxMp;
    _turnRecoverMp = turnRecoverMp;
}

/// <summary>
/// 回血
/// </summary>
/// <param name="amount"></param>
void CharacterModel::Heal(int amount)
{
    // TODO: muliao实现
}

/// <summary>
/// 扣血
/// </summary>
/// <param name="amount"></param>
void CharacterModel::TakeDamage(int amount)
{
    // TODO: muliao实现
}

/// <summary>
/// 回复魔法值
/// </summary>
/// <param name="amount"></param>
void CharacterModel::AddMp(int amount)
{
    // TODO: muliao实现
}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void CharacterModel::ReduceMp(int amount)
{
    // TODO: muliao实现
}

/// <summary>
/// 增加经验值
/// </summary>
/// <param name="amount"></param>
void CharacterModel::AddExp(int amount)
{
    // TODO: muliao实现
}

/// <summary>
/// 升级
/// </summary>
/// <param name="levelCount">升级等级数</param>
void CharacterModel::LevelUp(int levelCount = 1)
{
    // TODO: muliao实现
}
