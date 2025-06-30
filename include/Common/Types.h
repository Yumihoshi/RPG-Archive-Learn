#pragma once

/// <summary>
/// 元素属性枚举
/// </summary>
enum class ElementType
{
    None,

    /// <summary>
    /// 火
    /// </summary>
    Fire,

    /// <summary>
    /// 冰
    /// </summary>
    Ice,

    /// <summary>
    /// 自然
    /// </summary>
    Grass,


    /// <summary>
    /// 飞行
    /// </summary>
    Fly,


    /// <summary>
    /// 幽灵
    /// </summary>
    Ghost,
};

/// <summary>
/// 阵营枚举
/// </summary>
enum class CampType
{
    None,
    Friend,
    Enemy
};
/// <summary>
/// 装备枚举
/// </summary>
enum class EquipType
{
    None,
    Decoration,
    Armor
};
enum class Skills
{
    Fire,
    //烈火连爆,伤害*1.5
    Ice ,
    //寒霜凝滞让对方无法行动3回合
    Grass,
    //青藤焕生回血20
    Fly,
    //空影迷踪增加闪避率0.1
    Ghost
    // 鬼雾蚀力让对方下降10%
};

