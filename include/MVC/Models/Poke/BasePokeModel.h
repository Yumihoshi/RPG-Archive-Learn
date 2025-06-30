#pragma once

#include <iostream>
#include <vector>
#include "../../../Common/Types.h"
#include "../../../Equipment/Armor.h"
#include "../../../Equipment/Decoration.h"

class BasePokeModel
{
public:
    BasePokeModel();
    BasePokeModel(std::string name, ElementType ele, int maxHp, int maxMp, int turnRecoverMp,
        CampType camp, int maxExp, int maxLevel, float critRate, float fleeRate, int damage);
    virtual void Init();

    // 回血
    void Heal(int amount);

    // 扣血
    virtual void TakeDamage(int amount);

    // 回复魔法值
    void AddMp(int amount);

    // 减少魔法值
    void ReduceMp(int amount);

    // 增加经验值
    void AddExp(int amount);

    // 升级
    void LevelUp(int levelCount = 1);

    // 获取装备的饰品
    [[nodiscard]] std::shared_ptr<Decoration> GetDecoration() const;
    // 获取装备的防具
    [[nodiscard]] std::shared_ptr<Armor> GetArmor() const;
    // 装备饰品
    void Equip(std::shared_ptr<Decoration> decoration);
    // 装备防具
    void Equip(std::shared_ptr<Armor> armor);
    // 卸下饰品
    void Unequip(EquipType equipType);

    void ResetCur();

    // Getters
    std::string GetName();
    [[nodiscard]] int GetCurHp() const;
    [[nodiscard]] int GetMaxHp() const;
    [[nodiscard]] int GetCurMp() const;
    [[nodiscard]] int GetMaxMp() const;
    [[nodiscard]] int GetCurExp() const;
    [[nodiscard]] int GetMaxExp() const;
    [[nodiscard]] int GetCurLevel() const;
    [[nodiscard]] int GetMaxLevel() const;
    CampType GetCamp();
    [[nodiscard]] float GetFleeRate() const;
    [[nodiscard]] float GetCritRate() const;
    [[nodiscard]] int GetDamage() const;
    ElementType GetElement();
    std::string GetStory();
    [[nodiscard]] unsigned int GetId() const;

    // Setters
    void SetStory(std::string story);
    void SetId(unsigned int id);
    void SetDamage(int damage);
    void SetMaxHp(int maxHp);
    void SetCritRate(float critRate);
    void SetMaxMp(int maxMp);
    void SetFleeRate(float fleeRate);

    // 检查是否存活
    [[nodiscard]] bool IsAlive() const;

protected:
    unsigned int _id;       // id
    std::string _name;      // 宝可梦名
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

    int _damage;        // 攻击力

    std::shared_ptr<Decoration> _decoration;        // 饰品
    std::shared_ptr<Armor> _armor;          // 防具

    std::string _story;
protected:
    // 数值随机扰动（0.9到1.1）
    virtual void PerturbAttribute();
private:
    bool CheckFlee() const;

    // 新增setter方法
    void SetCurHp(int curHp) { _curHp = curHp; }
    void SetCurMp(int curMp) { _curMp = curMp; }
    void SetCurExp(int curExp) { _curExp = curExp; }
    void SetCurLevel(int curLevel) { _curLevel = curLevel; }
};
