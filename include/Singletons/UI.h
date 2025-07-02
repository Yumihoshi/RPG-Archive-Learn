/*******************************************************************************
* @author: Yumihoshi
* @email: xiaoyuesun915@gmail.com
* @creationDate: 2025/7/2 下午2:14
* @version: 1.0
* @description: 
*******************************************************************************/
#ifndef RPG_UI_H
#define RPG_UI_H

#include <vector>
#include "../Base/Singleton.h"
#include "../Poke/Pokemon.h"

class UI : public Singleton<UI>
{
public:
    void displayAllPokemon(
            const std::vector<std::shared_ptr<Pokemon>> &pokemonList) const;

    void displayBattleStatus() const;

private:
    UI() = default;

    friend class Singleton<UI>;
};


#endif //RPG_UI_H
