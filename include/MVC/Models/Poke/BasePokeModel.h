#pragma once

#include <iostream>
#include <vector>
#include "../../../Common/Types.h"
#include "../../../Equipment/Armor.h"
#include "../../../Equipment/Decoration.h"
#include "FirePokeModel.h"
#include "GrassPokeModel.h"
#include "IcePokeModel.h"
#include "FlyPokeModel.h"
#include "GhostPokeModel.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
    void SetCamp(CampType camp);
    void SetElement(ElementType element);
    void SetName(std::string name);
    void SetStory(std::string story);
    void SetId(unsigned int id);
    void SetDamage(int damage);
    void SetMaxHp(int maxHp);
    void SetCritRate(float critRate);
    void SetMaxMp(int maxMp);
    void SetFleeRate(float fleeRate);
    void SetMaxExp(int maxExp);
    void SetMaxLevel(int maxLevel);
    void SetDecoration(std::shared_ptr<Decoration> decoration);
    void SetArmor(std::shared_ptr<Armor> armor);

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

    std::vector<std::shared_ptr<Skill>> _skills; // 宝可梦技能
protected:
    // 数值随机扰动（0.9到1.1）
    virtual void PerturbAttribute();
private:
    bool CheckFlee() const;
public:
    // 新增setter方法
    void SetCurHp(int curHp) { _curHp = curHp; }
    void SetCurMp(int curMp) { _curMp = curMp; }
    void SetCurExp(int curExp) { _curExp = curExp; }
    void SetCurLevel(int curLevel) { _curLevel = curLevel; }

    // 计算伤害
    int CalculateDamage(float critRateBonus = 0.0f);
    // 检查是否暴击
    bool CheckCrit(float critRateBonus = 0.0f);
    // 检查是否闪避
    bool CheckFlee(float fleeRateBonus = 0.0f);

    friend void to_json(json& j, const BasePokeModel& p);
    friend void from_json(const json& j, BasePokeModel& p);

    static std::shared_ptr<BasePokeModel> CreateFromJson(const json& j);
};

inline void to_json(json& j, const BasePokeModel& p) {
    j = json{
        {"_id", p._id},
        {"_name", p._name},
        {"_element", p._element},
        {"_camp", p._camp},
        {"_curHp", p._curHp},
        {"_maxHp", p._maxHp},
        {"_curMp", p._curMp},
        {"_maxMp", p._maxMp},
        {"_turnRecoverMp", p._turnRecoverMp},
        {"_curExp", p._curExp},
        {"_maxExp", p._maxExp},
        {"_curLevel", p._curLevel},
        {"_maxLevel", p._maxLevel},
        {"_fleeRate", p._fleeRate},
        {"_critRate", p._critRate},
        {"_damage", p._damage},
        {"_story", p._story}
    };
    if (p._decoration) {
        j["_decoration"] = *p._decoration;
    }
    if (p._armor) {
        j["_armor"] = *p._armor;
    }
}

inline void from_json(const json& j, BasePokeModel& p) {
    j.at("_id").get_to(p._id);
    j.at("_name").get_to(p._name);
    j.at("_element").get_to(p._element);
    j.at("_camp").get_to(p._camp);
    j.at("_curHp").get_to(p._curHp);
    j.at("_maxHp").get_to(p._maxHp);
    j.at("_curMp").get_to(p._curMp);
    j.at("_maxMp").get_to(p._maxMp);
    j.at("_turnRecoverMp").get_to(p._turnRecoverMp);
    j.at("_curExp").get_to(p._curExp);
    j.at("_maxExp").get_to(p._maxExp);
    j.at("_curLevel").get_to(p._curLevel);
    j.at("_maxLevel").get_to(p._maxLevel);
    j.at("_fleeRate").get_to(p._fleeRate);
    j.at("_critRate").get_to(p._critRate);
    j.at("_damage").get_to(p._damage);
    j.at("_story").get_to(p._story);

    if (j.contains("_decoration")) {
        p._decoration = std::make_shared<Decoration>(j.at("_decoration").get<Decoration>());
    }
    if (j.contains("_armor")) {
        p._armor = std::make_shared<Armor>(j.at("_armor").get<Armor>());
    }
}
