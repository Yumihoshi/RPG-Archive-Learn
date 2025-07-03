#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "../Poke/Pokemon.h"
#include "../User/User.h"
#include "../Base/Singleton.h"
#include "../Common/Types.h"

class Game : public Singleton<Game>
{
public:
    std::shared_ptr<User> currentUser;
    std::shared_ptr<Pokemon> playerActivePokemon;
    std::shared_ptr<Pokemon> enemyActivePokemon;
public:
    // 游戏运行
    void run();

    // 清除输入缓冲区
    void clearInputBuffer();

    // 菜单
    void loginMenu();

    // 注册
    void adminMenu();

    // 玩家主菜单
    void playerMainMenu();

    // 载入菜单
    void saveLoadMenu();

    // 选择初始宝可梦
    void chooseInitialPokemon(std::shared_ptr<User> player);

    // 开始战斗
    void startBattle();

    // 载入玩家存档
    void loadPlayerSave(std::shared_ptr<User> player, int slotIndex);

    // 保存玩家存档
    void savePlayerSave(std::shared_ptr<User> player, int slotIndex);

    // 选择出战宝可梦
    void
    selectActivePokemon(std::vector<std::shared_ptr<Pokemon>> &pokemonList);

    // 管理员查看用户存档
    void adminViewUserSave();

    // 管理员管理用户宝可梦
    void adminManageUserPokemon();

    // 管理员管理用户装备
    void adminManageUserPokemonEquipment();

private:
    Game();

    friend class Singleton<Game>;

    // 战斗

    void battleTurn(std::shared_ptr<Pokemon> attacker,
                    std::shared_ptr<Pokemon> defender, bool isSkill = false);

    int
    calculateDamage(std::shared_ptr<Pokemon> attacker,
                    std::shared_ptr<Pokemon> defender, bool isSkill = false);

    bool checkEvasion(std::shared_ptr<Pokemon> defender);

    bool checkCritical(std::shared_ptr<Pokemon> attacker);

    void battleOutcome(bool playerWon);
};

#endif // GAME_H
