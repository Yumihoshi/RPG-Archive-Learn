#include "CharacterModel.h"

CharacterModel::CharacterModel(const std::string& name, ProfessionType profession, int maxHp, int maxMp, int turnRecoverMp)
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

}

/// <summary>
/// 减少魔法值
/// </summary>
/// <param name="amount"></param>
void CharacterModel::ReduceMp(int amount)
{

}
