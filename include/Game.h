#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Pokemon.h"
#include "User.h"

class Game {
public:
    Game();
    void run();

private:
    UserManager userManager;
    User* currentUser;

    void showLoginScreen();
    void showAdminMenu();
    void showPlayerMainMenu();
    void showSaveLoadMenu();
    void showPokemonManagementMenu();
    void startBattle();

    void createNewPlayerSave(User* player);
    void loadPlayerSave(User* player, int slotIndex);
    void savePlayerSave(User* player, int slotIndex);

    void displayAllPokemon(const std::vector<Pokemon>& pokemonList) const;
    void equipPokemon(Pokemon* pokemon);
    void unequipPokemon(Pokemon* pokemon);
    void selectActivePokemon(std::vector<Pokemon>& pokemonList);

    // Battle related
    Pokemon* playerActivePokemon;
    Pokemon* enemyActivePokemon;

    void battleTurn(Pokemon* attacker, Pokemon* defender, bool isSkill = false);
    int calculateDamage(Pokemon* attacker, Pokemon* defender, bool isSkill = false);
    bool checkEvasion(Pokemon* defender);
    bool checkCritical(Pokemon* attacker);
    void displayBattleStatus() const;
    void battleOutcome(bool playerWon);
};

#endif // GAME_H
