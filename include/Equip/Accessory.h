/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午1:40
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_ACCESSORY_H
#define RPG_ACCESSORY_H

#include <memory>
#include "Equipment.h"

class Accessory : public Equipment
{
public:
    Accessory(std::string name, int attackBonus, int magicBonus,
              double criticalRateBonus);

    int attackBonus;
    int magicBonus;
    double criticalRateBonus;

    void applyEffect(std::shared_ptr<Pokemon> pokemon) override;

    void removeEffect(std::shared_ptr<Pokemon> pokemon) override;

    void displayStats() const override;

    nlohmann::json toJson() const;

    static std::shared_ptr<Accessory> fromJson(const nlohmann::json &j);

    // Copy constructor and assignment operator
    Accessory(const Accessory &other);

    Accessory &operator=(const Accessory &other);
};


#endif //RPG_ACCESSORY_H
