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
    void run();

    void clearInputBuffer();

    void loginMenu();

    void adminMenu();

    void playerMainMenu();

    void saveLoadMenu();

    void chooseInitialPokemon(std::shared_ptr<User> player);

    void startBattle();

    void loadPlayerSave(std::shared_ptr<User> player, int slotIndex);

    void savePlayerSave(std::shared_ptr<User> player, int slotIndex);

    void
    selectActivePokemon(std::vector<std::shared_ptr<Pokemon>> &pokemonList);

    void adminViewUserSave();

    void adminManageUserPokemon();

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
