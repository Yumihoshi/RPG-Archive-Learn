/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午1:41
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ARMOR_H
#define RPG_ARMOR_H

#include <memory>
#include "Equipment.h"

class Armor : public Equipment
{
public:
    Armor(std::string name, int healthBonus, double evasionRateBonus);

    int healthBonus;
    double evasionRateBonus;

    void applyEffect(std::shared_ptr<Pokemon> pokemon) override;

    void removeEffect(std::shared_ptr<Pokemon> pokemon) override;

    void displayStats() const override;

    nlohmann::json toJson() const;

    static std::shared_ptr<Armor> fromJson(const nlohmann::json &j);

    // 复制构造函数和赋值运算符
    Armor(const Armor &other);

    Armor &operator=(const Armor &other);
};


#endif //RPG_ARMOR_H
